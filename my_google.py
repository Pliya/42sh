#!/usr/bin/env python3
##
## EPITECH PROJECT, 2024
## 42sh
## File description:
## my_google
##

from googlesearch import search

def google_search(query):
    for result in search(query, num_results=5):
        print(result)

if __name__ == "__main__":
    query = input("Enter your search query: ")
    google_search(query)
