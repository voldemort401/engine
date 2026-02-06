#!/usr/bin/env python3
import ipaddress
import os
from re import L 
from dotenv import load_dotenv
from typing import Sized
from nicegui import app, ui

load_dotenv()
ui.add_css(content= '''
            .primary_text{
                color: #EAF0FF;
            }
            .secondary_text{
                color: #9AA4FF;
            }
            .buttons{
                background: #11162A;
                transition-duration: 0.4s;
            }

            .buttons:hover {
                  background-color: #8B5CFF55;
            }

            .dialogs{
                background-color: #07080D;
            }

           ''')

def create_board(Bbishop, Bking,) -> None:
    DARK  = "#0E1020"
    LIGHT = "#1A1F3C"
    squares = {
    "a1": DARK,  "b1": LIGHT, "c1": DARK,  "d1": LIGHT, "e1": DARK,  "f1": LIGHT, "g1": DARK,  "h1": LIGHT,
    "a2": LIGHT, "b2": DARK,  "c2": LIGHT, "d2": DARK,  "e2": LIGHT, "f2": DARK,  "g2": LIGHT, "h2": DARK,
    "a3": DARK,  "b3": LIGHT, "c3": DARK,  "d3": LIGHT, "e3": DARK,  "f3": LIGHT, "g3": DARK,  "h3": LIGHT,
    "a4": LIGHT, "b4": DARK,  "c4": LIGHT, "d4": DARK,  "e4": LIGHT, "f4": DARK,  "g4": LIGHT, "h4": DARK,
    "a5": DARK,  "b5": LIGHT, "c5": DARK,  "d5": LIGHT, "e5": DARK,  "f5": LIGHT, "g5": DARK,  "h5": LIGHT,
    "a6": LIGHT, "b6": DARK,  "c6": LIGHT, "d6": DARK,  "e6": LIGHT, "f6": DARK,  "g6": LIGHT, "h6": DARK,
    "a7": DARK,  "b7": LIGHT, "c7": DARK,  "d7": LIGHT, "e7": DARK,  "f7": LIGHT, "g7": DARK,  "h7": LIGHT,
    "a8": LIGHT, "b8": DARK,  "c8": LIGHT, "d8": DARK,  "e8": LIGHT, "f8": DARK,  "g8": LIGHT, "h8": DARK,
    }
    __squares_only = list(squares.keys())
    
    with ui.grid(columns=8, rows=8) as grid:
        for x in range(64):
            color  = squares.get(__squares_only[x])
            ui.button().props(f"id={__squares_only[x]}").style(f'background-color: {color}').props('flat color=adaptive')
    
def recv(engine_ip, port):
    pass

def send():
    pass

def engine_dialog() -> None:
    # create the dialog window
    with ui.dialog() as dialog, ui.card().classes('dialogs'):
        
        ui.button(icon="close", on_click=dialog.close).classes('buttons ml-auto').props('flat')

        ## text area for the ip and port 
        with ui.grid(columns=2):
            engine_ip = ui.input(label="Engine Server IP").style('background-color: #0C0E1A').props('dark')\
                        .bind_value(app.storage.user, 'engine_ip')

            port_ip = ui.input(label="Port").style('background-color: #0C0E1A').props('dark')\
                      .bind_value(app.storage.user, 'engine_port')
            
            # verifying user input
            if (port_ip.value == ""):
                ui.notify('Please enter the port', type="negative", close_button="Dismiss")
            else:
                try:
                    int(app.storage.user.get('engine_port'))
                except ValueError:
                    ui.notify('Invalid Port', type="negative", close_button="Dismiss")

            if (engine_ip.value != ""):
                try:
                    ipaddress.ip_address(app.storage.user.get('engine_ip'))
                except ValueError:
                    ui.notify('Invalid IP Address', type="negative", close_button="Dismiss")
                    app.storage.user.pop('engine_ip')
            else:
                ui.notify('Please enter the ip', type="negative", close_button="Dismiss")

    #actually opening the dialog
    dialog.open()

def page_layout() -> None:
    LEFT_AND_RIGHT_DRAWER_BG = "#0B0E17"
    create_board()
    with ui.header(elevated=True).style('background-color: #161C3A').classes('items-center justify-between'):
        ui.space()
        ui.button(on_click=lambda: right_drawer.toggle(), icon="menu").classes('buttons').props('flat color=accent')


    with ui.left_drawer(top_corner=True, bottom_corner=True).style(f'background-color: {LEFT_AND_RIGHT_DRAWER_BG}'):
        ui.button(on_click=engine_dialog, icon="build_circle", text="engine").classes('buttons').props('flat color=accent')
        pass

    with ui.right_drawer(fixed=False).style(f'background-color: {LEFT_AND_RIGHT_DRAWER_BG}') as right_drawer:
        pass

def root() -> None:
    background_color = "#07080D"
    ui.query('body').style(f'background-color: {background_color}')
    ui.label("Chess engine").classes('primary_text')
    page_layout() 

secret = os.getenv("SECRET_KEY")
ui.run(storage_secret=secret,root=root())
