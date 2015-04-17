cuckvid: Because other codecs take too many clocks

Made by GreaseMonkey, 2015 - public domain

This is a video codec made so I could play 240x160 24fps video on a Game Boy Advance. The encoder is crap, but you get recognisable results.

This software is provided "as-is". No effort has been made to even pretend to port it to Windows, but it will probably work anyway. It also uses its own toolchain.

As this is a pure video codec, there's also an IMA ADPCM decoder for audio. I personally use sox to downsample and convert as ffmpeg's resampler is terrible. As raw audio doesn't take up several GB (UNLIKE RAW VIDEO THANK YOU VERY MUCH), the audio conversion step isn't handled in encode.sh, as you only need to convert once (plus IMA ADPCM audio encoders are actually good).

Codec rate is CBR 225.0 kbps (real kilobits, not this 1000 bullshit, if you're wondering it's 230.4 bskbps), or 28800B/s - 1200 bytes per frame. Format is 2:3:3 RGB.

There is PLENTY of room for improvement. Go nuts.

