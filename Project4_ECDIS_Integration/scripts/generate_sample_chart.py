#!/usr/bin/env python3
from pathlib import Path
import struct

root = Path(__file__).resolve().parent.parent
output_path = root / "data" / "sample_chart.s57"
output_path.parent.mkdir(parents=True, exist_ok=True)

features = [
    (1, 1001, [(0.0, 0.0)], "Buoy A"),
    (2, 1002, [(-5.0, -2.0), (0.0, 1.5), (5.0, 2.5)], "Shipping Lane"),
    (3, 1003, [(-8.0, -4.0), (-6.0, 4.0), (6.0, 5.0), (8.0, -3.0)], "Shallow Area"),
]

with output_path.open("wb") as out:
    out.write(b"S57MINI\0")
    out.write((1).to_bytes(1, "little"))
    out.write((len(features)).to_bytes(4, "little"))

    for type_id, feature_id, vertices, name in features:
        out.write(type_id.to_bytes(1, "little"))
        out.write(feature_id.to_bytes(4, "little"))
        out.write(len(vertices).to_bytes(4, "little"))
        for lon, lat in vertices:
            out.write(struct.pack("<d", lon))
            out.write(struct.pack("<d", lat))
        out.write(len(name).to_bytes(2, "little"))
        out.write(name.encode("utf-8"))

print(f"Generated sample chart: {output_path}")
