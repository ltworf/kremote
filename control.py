import dbus

_session_bus = dbus.SessionBus()

class Player(object):
    @classmethod
    def is_running(cls):
        '''Tries to connect to the player using dbus. If the player is not open
        (or if it is not possible to connect to it for other reasons) it will
        return False'''
        
        try:
            cls()
            return True
        except:
            return False

class Kaffeine(Player):
    def __init__(self):
        d =_session_bus.get_object('org.kde.kaffeine','/Player')
        
        self.pause = d.get_dbus_method('Pause','org.freedesktop.MediaPlayer')
        self.next = d.get_dbus_method('Next','org.freedesktop.MediaPlayer')
        self.prev = d.get_dbus_method('Prev','org.freedesktop.MediaPlayer')
        self.pause = d.get_dbus_method('PlayPause','org.freedesktop.MediaPlayer')
        self.volup = lambda x:d.get_dbus_method('VolumeSet','org.freedesktop.MediaPlayer')(d.get_dbus_method('VolumeGet','org.freedesktop.MediaPlayer')()+x)
        self.voldown = lambda x: self.volup(-x)

class Amarok(Player):
    def __init__(self):
        d =_session_bus.get_object('org.kde.amarok','/Player')
        
        self.pause = d.get_dbus_method('PlayPause','org.freedesktop.MediaPlayer')
        self.next = d.get_dbus_method('Next','org.freedesktop.MediaPlayer')
        self.prev = d.get_dbus_method('Prev','org.freedesktop.MediaPlayer')
        self.volup = d.get_dbus_method('VolumeUp','org.freedesktop.MediaPlayer')
        self.voldown = d.get_dbus_method('VolumeDown','org.freedesktop.MediaPlayer')
    pass