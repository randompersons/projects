#script interacts with the spotify API to create a playlist in my profile

import requests

SPOTIFY_CREATE_PLAYLIST_URL = f'https://api.spotify.com/v1/users/{user_id}/playlists'
ACCESS_TOKEN = 'BQDVRO9bjCLFZOn2PgYsTotZeUMg3lRsfckjZT5J3W2Ni4KN76LtEsQHbbK83UcLxlMxfibbhpSvoLcfr5MqzvxXFF9Rf57iD92RmGA0CJ00blcGWJwVHAnxiF5OmYyPIFGLLVpdWhWdrRd9QN50gOkiqr_53CWze9RN_y2fI0LeLxtM48ATR0CtsxPnX9mFpPcb4ta4DZx0LAN-9YtMVO0ukzaElaCT'


def create_playlist_on_spotify(name, public):
	response = requests.post
		SPOTIFY_CREATE_PLAYLIST_URL,
		headers={
			"Authorization": f"Bearer {ACCESS_TOKEN}"
		},
		json={
			"name": name,
			"public": public
		}
	)
	json_resp = response.json()

	return json_resp

def main():
	create_playlist_on_spotify(name, public)

if __name__ == '__main__':
	main()

