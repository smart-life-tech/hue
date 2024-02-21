import requests

url = 'https://maker.ifttt.com/trigger/k1off/with/key/d5GVBgd3oJf4bXzDph1-0xdiyoIB53Zhw2FufYp6a05'
data = {"value1": "red"}
headers = {"Content-Type": "application/json"}

response = requests.post(url, json=data, headers=headers)

if response.status_code == 200:
    print("IFTTT event triggered successfully.")
else:
    print(f"Failed to trigger IFTTT event. Status code: {response.status_code}")
    print(response.text)
