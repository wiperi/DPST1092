from operator import imod
import requests
from bs4 import BeautifulSoup
import os
from py_download import download_file


def extract_urls(url):
    """Extracts all URLs from the given webpage.

    Args:
        url: The URL of the webpage to scrape.

    Returns:
        A list of URLs found on the webpage.
    """
    try:
        response = requests.get(url)
        response.raise_for_status()  # Raise an exception for unsuccessful requests

        soup = BeautifulSoup(response.content, "html.parser")

        # Find all anchor tags (<a>)
        links = soup.find_all("a")

        # Create a dictionary to avoid duplicate URLs
        hash = {}

        urls = []
        for link in links:
            # Extract the href attribute (URL)
            href = link.get("href")
            if href and (href.endswith("slides")):  # Check if it ends with ".c"

                if href not in hash:
                    # href not in hash, add it to the list
                    hash[href] = True
                else:
                    # href in hash, skip this URL
                    continue

                urls.append(href)

        return urls
    except requests.exceptions.RequestException as e:
        print(f"Error fetching webpage: {e}")
        return []


if __name__ == "__main__":
    # Example usage
    url = "https://cgi.cse.unsw.edu.au/~cs1521/23T3/"  # Replace with the actual URL
    tar_dir = "C:/Users/15617/OneDrive/13 UNSW Y1T1/27 Computer System Fundamental/ppt"

    urls = extract_urls(url)

    if urls:
        # Show the extracted URLs
        print("Extracted URLs:")
        for url in urls:
            print(url)
            
        # Prompt the user to start the download
        print(f"Files will be downloaded to: {tar_dir}")
        user_input = input("Enter 'y' to start download: ")
        if user_input.lower() == 'y':
            for url in urls:
                # download files
                download_file(url, tar_dir, ".pdf")
        else:
            print("Download cancelled by user.")
    else:
        # No URLs found
        print("No URLs found on the webpage.")
