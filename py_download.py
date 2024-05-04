import requests
import os


def download_file(url, dest_folder):
    """Downloads a file from the specified URL and saves it in the given folder,
       preserving the original filename.

    Args:
        url: The URL of the file to download.
        dest_folder: The path of the folder where the file will be saved.
    """

    try:
        response = requests.get(url, stream=True)
        response.raise_for_status()  # Raise an exception for unsuccessful downloads

        # Extract the filename from the URL
        filename = url.split("/")[-1]

        # Create the destination path if it doesn't exist
        os.makedirs(dest_folder, exist_ok=True)

        # Construct full output path with the original filename
        file_path = os.path.join(dest_folder, filename)

        with open(file_path, "wb") as f:
            for chunk in response.iter_content(1024):
                f.write(chunk)

        print(f"File downloaded successfully to: {file_path}")
    except requests.exceptions.RequestException as e:
        print(f"Download failed: {e}")

if __name__ == "__main__":
    # Example usage
    url = (
        "https://csapp.cs.cmu.edu/3e/ics3/code/src/csapp.c"
    )
    # dest_folder = "C:/Users/15617/Documents/92_MyGithub/CSAPP/MIPS_demo/data"  # Replace with your desired folder path
    dest_folder = os.path.dirname(os.path.realpath(__file__))

    download_file(url, dest_folder)

    # if url[-1] == "c":
    #     url = url[:-1] + "s"
    # else:
    #     url = url[:-1] + "c"

    # download_file(url, dest_folder)
