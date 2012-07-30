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

    def sendRules(self, inf_rules, ruleset):
        self.profileManager.updateInferenceRules(self, inf_rules)
        for rule in ruleset:
            self.profileManager.addRule(self, rule)
        

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
        def javaProficience(classes):
            return classes.count_subclasses('AndreJavaLessons') == classes.count_subclasses('JavaRequirement')
        Application.sendRules(self, rules, [
            ('JavaProficience', bool, javaProficience),
        ])

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

class Class:
    pass

class Eprofile:

    def __init__(self):
        self.apps = set()
        self.contextInfo = {}
        self.events = {}
        self.inference = {}
        self.rules = {}
        self.classes = {}

    def registerApp(self, app):
        logging.info('Application ' + app.name + ' registered.')
        self.apps.add(app)
        self.contextInfo[app] = None
        self.inference[app] = None
        self.events[app] = []
        self.rules[app] = []
        self.classes[app] = []

    def updateContextInfo(self, app, context):
        logging.info('Context information for app ' + app.name + ' updated.')
        self.contextInfo[app] = context

    def updateInferenceRules(self, app, rules):
        logging.info('Inference rules for app ' + app.name + ' updated.')
        self.inference[app] = rules

    def addRule(self, app, rule):
        self.rules[app].append(rule)
        logging.info('New rule for app ' + app.name + ', field ' + rule[0] + '.')

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
            rulesTree = etree.fromstring(self.inference[app])
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

    def updateProfiles(self):
        f = open('temp.txt', 'r')
        for line in f:
            if len(line.strip()) == 0:
                continue
            init_spaces = 0
            while line[init_spaces:(init_spaces+1)] == ' ':
                init_spaces += 1
            level = (init_spaces - 1) / 3
            print(line + str(level))
        f.close()
            
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

    # eProfile do its thing
    eprofile.retrieveEvents()
    eprofile.reason()
    eprofile.updateProfiles()
