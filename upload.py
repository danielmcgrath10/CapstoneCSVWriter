# Code for uploading CSV to Google Spreadsheet
# Heavily influenced by https://medium.com/craftsmenltd/from-csv-to-google-sheet-using-python-ef097cb014f9

import csv
import os
import sys

import gspread
from oauth2client.service_account import ServiceAccountCredentials
import tkinter as tk
from tkinter import filedialog

# Settings for oauth2client library
scope=["https://spreadsheets.google.com/feeds", 'https://www.googleapis.com/auth/spreadsheets',
         "https://www.googleapis.com/auth/drive.file", "https://www.googleapis.com/auth/drive"]

# In order to run this, you need a client_secret.json file (See the link above on how to create)
credentials = ServiceAccountCredentials.from_json_keyfile_name('client_secret.json', scope)
# Authorizing the credentials passed
client = gspread.authorize(credentials)

# Opening the spreadsheet passed when you run the command "python upload.py <insert spreadsheet name>"
spreadsheet = client.open(sys.argv[1])

# Instantiating the tkinter widget
root = tk.Tk()
root.withdraw()

# Popping open a file dialog so that a user can select the CSV to upload to the Google sheet
file_path = filedialog.askopenfilename()
# Getting the file name from the file path
file_name = os.path.basename(file_path)
# Wrapping the attempt to open a worksheet and delete it if it exists
try:
    worksheet = spreadsheet.worksheet(file_name)
    spreadsheet.del_worksheet(worksheet)
except:
    print('file does not exist')

# Adding a worksheet with the same name as the file to the Google spreadsheet
worksheet = spreadsheet.add_worksheet(title=file_name,rows='100', cols='20')

# Opening the CSV and writing the contents to the Google Sheet
with open(file_path, 'r', encoding='utf-8') as file_obj:
    csv_reader = csv.reader(file_obj)

    lists_from_csv = []
    for row in csv_reader:
        lists_from_csv.append(row)

    worksheet.append_rows(lists_from_csv)
