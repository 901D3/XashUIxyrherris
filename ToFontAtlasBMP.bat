:: max color pallete: 16

magick -size 16x1 gradient:black-white -colorspace RGB palette.bmp
magick input.bmp -alpha off -colorspace Gray -dither None -remap palette.bmp -depth 4 BMP3:output.bmp
