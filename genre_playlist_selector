from tkinter import *
from tkinter.ttk import *

import spotipy
import spotipy.util as util

from spotipy.oauth2 import SpotifyClientCredentials

import pandas as pd

cid = '4e0eba88924849ddbc5d483b88b6a148'
secret = '6fe0b68727fb41daa2e13aaa1e4e48ed'

username = "xsd7gkl0pozddzfnblvhvg4lk"
scope = "user-modify-playback-state"

redirect_uri = "http://localhost:8888/callback"

token = util.prompt_for_user_token(username, scope, cid, secret, redirect_uri)
sp = spotipy.Spotify(auth=token)


def main():
	window = Tk()
	window.geometry("200x200")
	label = Label(window,
        text ="This is the main window")
	label.pack(pady = 10)
	
	btn1 = Button(window,
             text ="Rap",
             command = lambda : sp.start_playback(device_id=None, context_uri="https://open.spotify.com/playlist/48bIdNU1cOt65cXxtugyqS?si=5810f0d7add04bd5", uris=None, offset=None, position_ms=None))
	btn1.pack(side = TOP)

	btn2 = Button(window,
             text ="Rock",
             command = lambda : sp.start_playback(device_id=None, context_uri="https://open.spotify.com/playlist/5m7l6HkCe80qSEjdLINbMS?si=47778ba890c442c3", uris=None, offset=None, position_ms=None))
	btn2.pack(side = LEFT)

	btn3 = Button(window,
             text ="Jazz",
             command = lambda : sp.start_playback(device_id=None, context_uri="https://open.spotify.com/playlist/2HvfyhrAn7iK2jBacL8aPr?si=de52de812a5a4994", uris=None, offset=None, position_ms=None))
	btn3.pack(side = RIGHT)

	btn4 = Button(window,
             text ="Dance",
             command = lambda : sp.start_playback(device_id=None, context_uri="https://open.spotify.com/playlist/55dqP4WpfijZbiGPVRXgms?si=573a07d69c4c4940", uris=None, offset=None, position_ms=None))
	btn4.pack(side = LEFT)



	mainloop()




if __name__ == '__main__':
	main()
