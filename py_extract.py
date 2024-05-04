from operator import imod
import requests
from bs4 import BeautifulSoup
import os
from py_download import download_file


def extract_c_urls(url):
    """Extracts all URLs ending with .c from the given webpage.

    Args:
        url: The URL of the webpage to scrape.

    Returns:
        A list of URLs ending with .c found on the webpage.
    """
    try:
        response = requests.get(url)
        response.raise_for_status()  # Raise an exception for unsuccessful requests

        soup = BeautifulSoup(response.content, "html.parser")

        # Find all anchor tags (<a>)
        links = soup.find_all("a")

        c_urls = []
        for link in links:
            # Extract the href attribute (URL)
            href = link.get("href")
            if href and (href.endswith(".c") or href.endswith(".s")):  # Check if it ends with ".c"
                c_urls.append(href)

        return c_urls
    except requests.exceptions.RequestException as e:
        print(f"Error fetching webpage: {e}")
        return []


if __name__ == "__main__":
    # Example usage
    url = "https://cgi.cse.unsw.edu.au/~cs1521/23T3/topic/floating_point/code/"  # Replace with the actual URL
    c_urls = extract_c_urls(url)

    if c_urls:
        print("Extracted URLs ending with .c:")
        for url in c_urls:
            print(url)
            
        user_input = input("Enter 'y' to start download: ")
        if user_input.lower() == 'y':
            for url in c_urls:
                # Download the file
                download_file(url, "C:/Users/15617/Documents/92_MyGithub/CSAPP/wk5_float")
        else:
            print("Download cancelled by user.")
    else:
        print("No URLs ending with .c found on the webpage.")
