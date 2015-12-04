#!/bin/sh

for resonance in `seq  1000 50 3000`
do
    python interpolate.py ~hinzmann/public/yxin/BulkWWCombined $resonance &
    python interpolate.py ~hinzmann/public/yxin/BulkZZCombined $resonance
done

for resonance in `seq  1000 50 3000`
do
    python interpolate.py ~hinzmann/public/yxin/RSGWWherwig $resonance &
    python interpolate.py ~hinzmann/public/yxin/RSGZZherwig $resonance &
    python interpolate.py ~hinzmann/public/yxin/RSGWWpythia $resonance &
    python interpolate.py ~hinzmann/public/yxin/RSGZZpythia $resonance &
    python interpolate.py ~hinzmann/public/yxin/Wprime $resonance
done

for resonance in `seq  1000 50 4000`
do
    python interpolate.py ~hinzmann/public/yxin/QstarQW $resonance &
    python interpolate.py ~hinzmann/public/yxin/QstarQZ $resonance
done
