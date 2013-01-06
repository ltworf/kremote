import notify2
notify2.init ('kremote')

def notify(message):
    n = notify2.Notification ('kremote',message,'multimedia-player')
    n.show ()