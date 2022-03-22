import spotipy

from spotipy.oauth2 import SpotifyClientCredentials

import pandas as pd

cid = ''
secret = ''

client_credentials_manager = SpotifyClientCredentials(client_id=cid, client_secret=secret)

sp = spotipy.Spotify(client_credentials_manager = client_credentials_manager)

def call_playlist(creator, playlist_id):

    playlist_features_list = ["artist","album","track_name",  "track_id"]
    
    playlist_df = pd.DataFrame(columns = playlist_features_list)
    
    playlist = sp.user_playlist_tracks(creator, playlist_id)["items"]
    for track in playlist:
        
        playlist_features = {}
        
        playlist_features["artist"] = track["track"]["album"]["artists"][0]["name"]
        playlist_features["album"] = track["track"]["album"]["name"]
        playlist_features["track_name"] = track["track"]["name"]
        playlist_features["track_id"] = track["track"]["id"]

        track_df = pd.DataFrame(playlist_features, index = [0])
        playlist_df = pd.concat([playlist_df, track_df], ignore_index = True)

    return playlist_df

def main():
	playlist_input = input("Input Playlist URL: ")
	creator = input("Input Playlist Creator: ")

	playlist_strip_1 = playlist_input[34:]

	sep = "?"
	playlist_id = playlist_strip_1.split(sep, 1)[0]

	info = call_playlist(creator, playlist_id)
	print(info)

if __name__ == '__main__':
	main()
