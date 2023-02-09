import { registerFont, createCanvas, type Canvas } from "canvas";
import * as path from "path";
import * as fs from "fs";
import { exit } from "process";

function main() {
  const bitmapPixelSize = 60;
  const charset = readCharset();
  const data: { char: string; raw: string, length: number }[] = [];

  for (const c of charset) {
    const canvas = setupCanvas(bitmapPixelSize);
    const ctx = canvas.getContext("2d");
    ctx.fillText(c, bitmapPixelSize / 2, bitmapPixelSize / 2);

    // debug: dump jpeg
    // writeFileSafe(`build/${c}.jpeg`, canvas.toBuffer("image/jpeg"));

    const buf = canvas.toBuffer("raw"); // BGRA order on little-endian (most)
    let raw = "";
    for (let i = 0; i < buf.length; i += 4) {
      const [b, g, r] = buf.subarray(i, i + 3);
      const average = (r + g + b) / 3;
      const v = average > 140 ? "1" : "0"; // 140 is determined by debug check.
      raw += v;
    }
    data.push({
      char: c,
      raw: raw,
      length: Buffer.byteLength(c)
    });
  }

  // debug: data check
  // for (const d of data) {
  //   for (let i = 0; i < bitmapPixelSize; i++) {
  //     console.log(d.raw.slice(bitmapPixelSize * i, bitmapPixelSize * (i + 1)));
  //   }
  //   console.log();
  // }

  writeFileSafe(
    "resources/chardata.txt",
    data.map((x) => `c:${x.length}${x.char}\nb:${x.raw}`).join("\n")
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
  ctx.antialias = "gray";
  ctx.font = `${size * 0.7}px Noto Sans JP`;
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
