import csv
import os
import sys

import gspread
from oauth2client.service_account import ServiceAccountCredentials
import tkinter as tk
from tkinter import filedialog

scope=["https://spreadsheets.google.com/feeds", 'https://www.googleapis.com/auth/spreadsheets',
         "https://www.googleapis.com/auth/drive.file", "https://www.googleapis.com/auth/drive"]
credentials = ServiceAccountCredentials.from_json_keyfile_name('client_secret.json', scope)
client = gspread.authorize(credentials)

spreadsheet = client.open(sys.argv[1])

root = tk.Tk()
root.withdraw()


file_path = filedialog.askopenfilename()
file_name = os.path.basename(file_path)
try:
    worksheet = spreadsheet.worksheet(file_name)
    spreadsheet.del_worksheet(worksheet)
except:
    print('file does not exist')

worksheet = spreadsheet.add_worksheet(title=file_name,rows='100', cols='20')

with open(file_path, 'r', encoding='utf-8') as file_obj:
    csv_reader = csv.reader(file_obj)

    lists_from_csv = []
    for row in csv_reader:
        lists_from_csv.append(row)

    worksheet.append_rows(lists_from_csv)



