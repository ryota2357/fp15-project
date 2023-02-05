import { registerFont, createCanvas, type Canvas } from "canvas";
import * as path from "path";
import * as fs from "fs";
import { exit } from "process";

function main() {
  const charset = readCharset();
  const data: { char: string; raw: string }[] = [];

  for (const c of charset) {
    const canvas = setupCanvas(40);
    const ctx = canvas.getContext("2d");
    ctx.fillText(c, 20, 20);

    // debug: dump jpeg
    // writeFileSafe(`build/${c}.jpeg`, canvas.toBuffer("image/jpeg"));

    const buf = canvas.toBuffer("raw"); // BGRA order on little-endian (most)
    let raw = "";
    for (let i = 0; i < buf.length; i += 4) {
      const [b, g, r] = buf.subarray(i, i + 3);
      const average = (r + g + b) / 3;
      const v = average > 100 ? "1" : "0"; // 100 is determined by looking at the jpeg.
      raw += v;
    }
    data.push({
      char: c,
      raw: raw,
    });
  }

  // debug: data check
  // for (const d of data) {
  //   for (let i = 0; i < 40; i++) {
  //     console.log(d.raw.slice(40 * i, 40 * (i + 1)));
  //   }
  //   console.log();
  // }

  writeFileSafe(
    "resources/chardata.txt",
    data.map((x) => `c:${x.char}\nb:${x.raw}`).join("\n")
  );
}

function setupCanvas(size: number): Canvas {
  registerFont(path.resolve("./assets/NotoSansJP-Medium.otf"), {
    family: "Noto Sans JP",
  });
  const canvas = createCanvas(size, size);
  const ctx = canvas.getContext("2d");
  ctx.textAlign = "center";
  ctx.textBaseline = "middle";
  ctx.fillStyle = "white";
  ctx.font = `${size}px Noto Sans JP`;
  return canvas;
}

function readCharset(): string[] {
  const text = fs.readFileSync("./assets/charset.txt").toString().trim();
  if (text.includes("\n")) {
    console.error("charset.txt must be 1 line.");
    exit(1);
  }
  const ret = new Set([...text.split("")]);
  return [...ret].sort();
}

function writeFileSafe(
  filePath: string,
  data: string | NodeJS.ArrayBufferView
) {
  const dir = path.parse(filePath).dir;
  if (!fs.existsSync(dir)) {
    fs.mkdirSync(dir, { recursive: true });
  }
  fs.writeFileSync(filePath, data);
}

main();
