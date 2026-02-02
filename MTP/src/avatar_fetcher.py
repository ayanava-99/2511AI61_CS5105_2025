import os
import requests
from pathlib import Path

def fetch_avatar(roll_no: str, save_dir: str) -> str | None:
    """
    Fetches an avatar for the given roll number from DiceBear API.
    Saves it to save_dir and returns the path.
    Returns None if fetching fails.
    """
    roll_no = str(roll_no).strip()
    if not roll_no:
        return None

    # Define the target path
    filename = f"{roll_no}.png"
    save_path = os.path.join(save_dir, filename)

    # Check if already exists (cache)
    if os.path.exists(save_path):
        return save_path

    # API URL (DiceBear Avataaars)
    # Using specific style 'avataaars' which is good for profile pics
    url = f"https://api.dicebear.com/7.x/avataaars/png?seed={roll_no}"

    try:
        response = requests.get(url, timeout=5)
        if response.status_code == 200:
            with open(save_path, "wb") as f:
                f.write(response.content)
            return save_path
    except Exception as e:
        print(f"Failed to fetch avatar for {roll_no}: {e}")
        return None

    return None
