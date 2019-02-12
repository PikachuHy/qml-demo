# https://github.com/jiaaro/pydub
from pydub import AudioSegment
song = AudioSegment.from_wav("/home/pikachu/Music/Pa.wav")
song.export("mashup.mp3", format="mp3")