import requests
from bs4 import BeautifulSoup
import urllib.parse
import os

def get_ppt_links(url):
    response = requests.get(url)
    soup = BeautifulSoup(response.content, 'html.parser')
    
    ppt_links = []
    for link in soup.find_all('a', href=True):
        href = link['href']
        if href.lower().endswith('.ppt') or href.lower().endswith('.pptx'):
            ppt_links.append((link.text.strip(), urllib.parse.urljoin(url, href)))
    
    return ppt_links

def display_ppt_links(ppt_links):
    if not ppt_links:
        print("No PPT files found.")
        return
    
    print("Found the following PPT files:")
    for i, (name, url) in enumerate(ppt_links):
        print(f"{i+1}. {name} ({url})")

def download_ppt_files(ppt_links):
    for name, url in ppt_links:
        filename = url.split('/')[-1]
        response = requests.get(url)
        with open(filename, 'wb') as f:
            f.write(response.content)
        print(f"Downloaded: {filename}")

def main():
    url = input("Enter the URL of the webpage to crawl: ").strip()
    ppt_links = get_ppt_links(url)
    
    if not ppt_links:
        print("No PPT files found on the webpage.")
        return
    
    display_ppt_links(ppt_links)
    
    download_choice = input("Do you want to download these files? (y/n): ").strip().lower()
    if download_choice == 'y':
        download_ppt_files(ppt_links)
    else:
        print("Download canceled.")

if __name__ == "__main__":
    main()
