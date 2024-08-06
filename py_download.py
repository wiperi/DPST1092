from stat import SF_APPEND
import requests
import os


def download_file(url, dest_folder, extention=None):
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

        # Add the file extension if provided
        if extention:
            filename += extention

        # Return if dest_folder does not exist
        if not os.path.exists(dest_folder):
            print(f"Destination folder does not exist: {dest_folder}")
            return

        # Construct full output path with the original filename
        file_path = os.path.join(dest_folder, filename)

        # Make sure the file does not already exist
        suffix = 1
        while os.path.exists(file_path):
            new_filename = filename.split(".")[0] + f"_{suffix}." + filename.split(".")[1]
            suffix += 1
            file_path = os.path.join(dest_folder, new_filename)

        # Download the file
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
