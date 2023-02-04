import * as path from "https://deno.land/std@0.176.0/path/mod.ts";

function main() {
  const script_dir = path.dirname(path.fromFileUrl(import.meta.url));
  const text = Deno.readTextFileSync(`${script_dir}/frames.txt`);

  const ret: string[] = [];
  const brailleList = createBrailleList();
  // NOTE: remove `\r\n` from line by trim()
  for (const line of text.split("\n").map((x) => x.trim())) {
    if (line.length == 0) {
      continue;
    }
    if (line.startsWith("00:")) {
      // t: time
      ret.push(`t:${line}`);
      continue;
    }
    if (/^[0-9]+$/.test(line)) {
      // c: count
      ret.push(`c:${line.padStart(4, "0")}`);
      continue;
    }
    if (brailleList.includes(line.at(0) ?? "*")) {
      // b: bitmap or braille
      ret.push("b:");
      for (let i = 0; i < line.length; ++i) {
        const num = brailleLetterToNum(line[i]);
        ret[ret.length - 1] += num.toString().padStart(3, "0");
        if (i != line.length - 1) {
          ret[ret.length - 1] += ",";
        }
      }
      continue;
    }
    throw Error(`Invalid line: ${line}`);
  }

  const encoder = new TextEncoder();
  const data = encoder.encode(ret.join("\n"));
  Deno.writeFileSync(`${script_dir}/frames2.txt`, data);
}

function createBrailleList(): string {
  let ret = "";
  for (let i = 0; i <= 0xFF; i++) {
    ret += numToBrailleLetter(i);
  }
  return ret;
}

// ① ⑤
// ② ⑥
// ③ ⑦
// ④ ⑧ に対して、⑧ ⑦ ⑥ ...① のビット列(number) との相互変換
// https://qiita.com/zakuroishikuro/items/15d1a69178895edf9a21#8%E7%82%B9%E7%82%B9%E5%AD%97
function numToBrailleLetter(n: number): string {
  let flags = 0;
  flags += (n & 0b00001000) << 3; //⑦ を左シフト
  flags += (n & 0b01110000) >> 1; //④ ⑤ ⑥ を右シフト
  flags += n & 0b10000111; //① ② ③ ⑧ はそのまま
  return String.fromCodePoint(flags + 0x2800);
}
function brailleLetterToNum(c: string): number {
  const u = c.codePointAt(0);
  if (u == undefined) {
    throw Error(`Invalid character: ${c}`);
  }
  let flags = 0;
  flags += (u & 0b01000000) >> 3;
  flags += (u & 0b00111000) << 1;
  flags += u & 0b10000111;
  return flags;
}

main();
