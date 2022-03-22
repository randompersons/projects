import requests

SPOTIFY_GET_PLAYLIST_URL = f'https://api.spotify.com/v1/playlists/{playlist_id}/tracks'
ACCESS_TOKEN = 'BQDVRO9bjCLFZOn2PgYsTotZeUMg3lRsfckjZT5J3W2Ni4KN76LtEsQHbbK83UcLxlMxfibbhpSvoLcfr5MqzvxXFF9Rf57iD92RmGA0CJ00blcGWJwVHAnxiF5OmYyPIFGLLVpdWhWdrRd9QN50gOkiqr_53CWze9RN_y2fI0LeLxtM48ATR0CtsxPnX9mFpPcb4ta4DZx0LAN-9YtMVO0ukzaElaCT'


#def create_playlist_on_spotify(name, public):
#	response = requests.post(
#		SPOTIFY_CREATE_PLAYLIST_URL,
#		headers={
#			"Authorization": f"Bearer {ACCESS_TOKEN}"
#		},
#		json={
#			"name": name,
#			"public": public
#		}
#	)
#	json_resp = response.json()
#
#	return json_resp

def get_playlist_items():
	response = requests.post(
		SPOTIFY_GET_PLAYLIST_URL,
		headers={
			"Authorization": f"Bearer {ACCESS_TOKEN}"
		},
		json=
		{
  			"href": "https://api.spotify.com/v1/xsd7gkl0pozddzfnblvhvg4lk/shows?offset=0&limit=50\n",
  			"items": [
			    {}
			  ],
			"limit": 50,
			"next": "null",
			"offset": 0,
			"previous": "null",
			"total": 3
		}
	)
	json_resp = response.json()


	return json_resp

def main():
	items = get_playlist_items()


	print(items)

if __name__ == '__main__':
	main()

