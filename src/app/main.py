from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.screenmanager import ScreenManager, Screen, SlideTransition
from kivy.uix.button import Button
from kivy.uix.scrollview import ScrollView
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
from kivy.uix.popup import Popup
import random

# Dummy data for chapters
random_paragraphs = [
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
    "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.",
    "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.",
    "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.",
    "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
]

class Tab:
    def __init__(self, name):
        self.name = name
        self.current_index = random.randint(0, len(random_paragraphs) - 1)

    def get_current_text(self):
        return random_paragraphs[self.current_index]

    def get_next_text(self):
        self.current_index = (self.current_index + 1) % len(random_paragraphs)
        return self.get_current_text()

    def get_previous_text(self):
        self.current_index = (self.current_index - 1) % len(random_paragraphs)
        return self.get_current_text()

class EntryScreen(Screen):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.layout = BoxLayout(orientation='vertical')

        self.tab_list = []

        # Tabs Container (2-column layout)
        self.tabs_container = BoxLayout(orientation='vertical', size_hint_y=None)
        self.tabs_container.bind(minimum_height=self.tabs_container.setter('height'))
        self.scroll = ScrollView()
        self.scroll.add_widget(self.tabs_container)

        # Control row with "Add Tab" button
        self.control_row = BoxLayout(size_hint_y=0.1)
        self.add_tab_button = Button(text="Add Tab")
        self.add_tab_button.bind(on_press=self.add_tab_popup)
        self.control_row.add_widget(self.add_tab_button)

        self.layout.add_widget(self.scroll)
        self.layout.add_widget(self.control_row)
        self.add_widget(self.layout)

    def add_tab_popup(self, instance):
        # Popup to prompt for a tab name
        content = BoxLayout(orientation='vertical')
        input_field = TextInput(hint_text="Enter tab name", multiline=False)
        content.add_widget(input_field)

        button_row = BoxLayout(size_hint_y=0.3)
        cancel_button = Button(text="Cancel")
        create_button = Button(text="Create")
        button_row.add_widget(cancel_button)
        button_row.add_widget(create_button)
        content.add_widget(button_row)

        popup = Popup(title="Create New Tab", content=content, size_hint=(0.7, 0.4))

        def create_tab(instance):
            tab_name = input_field.text.strip()
            if not tab_name:
                popup.title = "Name cannot be empty"
                return
            if any(tab.name == tab_name for tab in self.tab_list):
                popup.title = "Tab name already exists"
                return

            self.add_tab(tab_name)
            popup.dismiss()

        create_button.bind(on_press=create_tab)
        cancel_button.bind(on_press=popup.dismiss)
        popup.open()

    def add_tab(self, tab_name):
        new_tab = Tab(tab_name)
        self.tab_list.append(new_tab)

        # Create a button for the new tab
        tab_button = Button(text=tab_name, size_hint=(0.5, None), height=40)
        tab_button.bind(on_press=lambda x: self.enter_tab(new_tab))

        # Add the button to the 2-column layout
        if len(self.tabs_container.children) == 0 or len(self.tabs_container.children[-1].children) == 2:
            row = BoxLayout(size_hint_y=None, height=40)
            self.tabs_container.add_widget(row)
        self.tabs_container.children[-1].add_widget(tab_button)

    def enter_tab(self, tab):
        self.manager.transition = SlideTransition(direction="left")
        tab_screen = self.manager.get_screen('tab_screen')
        tab_screen.set_tab(tab)
        self.manager.current = "tab_screen"

class TabScreen(Screen):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.layout = BoxLayout(orientation='vertical')

        # Scrollable text
        self.scroll = ScrollView(size_hint_y=0.9)
        self.label = Label(size_hint_y=None, height=200, text_size=(400, None), halign='left', valign='top')
        self.label.bind(texture_size=self.label.setter('size'))
        self.scroll.add_widget(self.label)

        # Control row with "Back" button
        self.control_row = BoxLayout(size_hint_y=0.1)
        self.back_button = Button(text="Back")
        self.back_button.bind(on_press=self.go_back)
        self.control_row.add_widget(self.back_button)

        self.layout.add_widget(self.scroll)
        self.layout.add_widget(self.control_row)
        self.add_widget(self.layout)

        self.current_tab = None

    def set_tab(self, tab):
        self.current_tab = tab
        self.label.text = tab.get_current_text()

    def go_back(self, instance):
        self.manager.transition = SlideTransition(direction="right")
        self.manager.current = "entry_screen"

    def on_touch_up(self, touch):
        if self.control_row.collide_point(*touch.pos):
            return super().on_touch_up(touch)

        if touch.x < self.width * 0.2:  # Swipe to the right
            if self.current_tab:
                self.label.text = self.current_tab.get_previous_text()
        elif touch.x > self.width * 0.8:  # Swipe to the left
            if self.current_tab:
                self.label.text = self.current_tab.get_next_text()
        return super().on_touch_up(touch)

class TabbedApp(App):
    def build(self):
        sm = ScreenManager()
        sm.add_widget(EntryScreen(name='entry_screen'))
        sm.add_widget(TabScreen(name='tab_screen'))
        return sm

if __name__ == '__main__':
    TabbedApp().run()
