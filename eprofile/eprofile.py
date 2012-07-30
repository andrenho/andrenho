import os
import xml.etree.ElementTree as etree

import logging
logging.basicConfig(level=logging.INFO)

class Application:
    trailManager = None
    profileManager = None
    name = 'None'

    def sendContext(self, context):
        self.profileManager.updateContextInfo(self, context)

    def sendRules(self, rules):
        self.profileManager.updateRules(self, rules)
        

#################################################################

class StudentApp(Application):
    name = 'StudentApp'

    def sendContext(self):
        f = open('things.xml')
        context = f.read()
        f.close()
        Application.sendContext(self, context)

    def sendRules(self):
        f = open('rules.xml')
        rules = f.read()
        f.close()
        Application.sendRules(self, rules)

    def registerRandomEvent(self):
        f = open('event.xml')
        event = f.read()
        f.close()
        self.trailManager.registerEvent(self, event)
        
#################################################################

class Event:
    
    def __init__(self, app, event):
        self.app = app
        self.event = event
        
class TrailManager:

    def __init__(self):
        self.events = []

    def registerEvent(self, app, event):
        self.events.append(Event(app, event))

    def sendEvents(self):
        evs = list(self.events)
        self.events = []
        return evs
        

#################################################################

class Eprofile:

    def __init__(self):
        self.apps = set()
        self.contextInfo = {}
        self.events = {}
        self.rules = {}

    def registerApp(self, app):
        logging.info('Application ' + app.name + ' registered.')
        self.apps.add(app)
        self.contextInfo[app] = None
        self.rules[app] = None
        self.events[app] = []

    def updateContextInfo(self, app, context):
        logging.info('Context information for app ' + app.name + ' updated.')
        self.contextInfo[app] = context

    def updateRules(self, app, rules):
        logging.info('Rules for app ' + app.name + ' updated.')
        self.rules[app] = rules

    def retrieveEvents(self):
        n = 0
        trail_managers = set([app.trailManager for app in self.apps])
        for tm in trail_managers:
            for event in tm.sendEvents():
                self.events[event.app].append(event.event)
                n += 1
        logging.info(str(n) + ' new event(s) retrieved from the trail managers.')

    def reason(self):
        for app in self.apps:
            # open up context information
            contextTree = etree.fromstring(self.contextInfo[app])
            # insert events
            eventTrees = []
            for event in self.events[app]:
                eventTrees.append(etree.fromstring(event))
            # insert reasoning
            rulesTree = etree.fromstring(self.rules[app])
            # merge all information
            for eventTree in eventTrees:
                for evt_el in eventTree.getchildren():
                    contextTree.append(evt_el)
            for rule_el in rulesTree:
                contextTree.append(rule_el)                
            # call reasoner
            f = open('temp.owl', 'wb')
            f.write(etree.tostring(contextTree))
            f.close()
            os.system('./reason')
            
#################################################################

if __name__ == '__main__':
    
    # initialize everything
    app = StudentApp()
    tm = TrailManager()
    eprofile = Eprofile()

    # connect the programs
    app.trailManager = tm
    app.profileManager = eprofile
    eprofile.registerApp(app)

    # application sends context information and rules
    app.sendContext()
    app.sendRules()

    # application register trails
    #for _ in range(50):
    app.registerRandomEvent()

    # eProfile retrieve events from trail managers
    eprofile.retrieveEvents()
    
    # eprofile
    eprofile.reason()
