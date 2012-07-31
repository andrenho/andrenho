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
            return classes.countSubclasses('AndreJavaLessons') == classes.countSubclasses('JavaRequirement')
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
    
    def __init__(self, name):
        self.name = name
        self.children = []

    def countSubclasses(self, name):
        def countSubclasses2(c, name):
            if c.name == name:
                return len(c.children)
            else:
                return sum([countSubclasses2(m, name) for m in c.children])
        return countSubclasses2(self, name)

class EprofileAppInfo:
    def __init__(self):
        self.contextInfo = None
        self.inference = None
        self.events = []
        self.rules = []
        self.rootClass = None
        self.profile = {}


class Eprofile:

    def __init__(self):
        self.apps = set()
        self.appInfo = {}

    def registerApp(self, app):
        logging.info('Application ' + app.name + ' registered.')
        self.apps.add(app)
        self.appInfo[app] = EprofileAppInfo()

    def updateContextInfo(self, app, context):
        logging.info('Context information for app ' + app.name + ' updated.')
        self.appInfo[app].contextInfo = context

    def updateInferenceRules(self, app, rules):
        logging.info('Inference rules for app ' + app.name + ' updated.')
        self.appInfo[app].inference = rules

    def addRule(self, app, rule):
        self.appInfo[app].rules.append(rule)
        logging.info('New rule for app ' + app.name + ', field ' + rule[0] + '.')

    def retrieveEvents(self):
        n = 0
        trail_managers = set([app.trailManager for app in self.apps])
        for tm in trail_managers:
            for event in tm.sendEvents():
                self.appInfo[event.app].events.append(event.event)
                n += 1
        logging.info(str(n) + ' new event(s) retrieved from the trail managers.')

    def reason(self):
        for app in self.apps:
            # open up context information
            contextTree = etree.fromstring(self.appInfo[app].contextInfo)
            # insert events
            eventTrees = []
            for event in self.appInfo[app].events:
                eventTrees.append(etree.fromstring(event))
            # insert reasoning
            rulesTree = etree.fromstring(self.appInfo[app].inference)
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
            self.appInfo[app].rootClass = self.interpretPelletOutput()

    def interpretPelletOutput(self):
        f = open('temp.txt', 'r')
        class_stack = []
        class_level = -1
        root = None
        for line in f:
            if len(line.strip()) == 0:
                continue
            init_spaces = 0
            while line[init_spaces:(init_spaces+1)] == ' ':
                init_spaces += 1
            level = int((init_spaces - 1) / 3)
            name = line[(line.find(':')+1):len(line)-1]

            c = Class(name)
            if not root:
                root = c
            if level > class_level:
                if len(class_stack) > 0:
                    class_stack[-1].children.append(c)
                class_stack.append(c)
            else:
                for _ in range(class_level - level + 1):
                    class_stack.pop()
                if len(class_stack) > 0:
                    class_stack[-1].children.append(c)
                class_stack.append(c)
            class_level = level            
        f.close()
        """
        def print_class(c, l=0):
            print((' ' * l * 2) + c.name)
            for ch in c.children:
                print_class(ch, l+1)
        print_class(root)
        """
        return root


    def updateProfiles(self):
        for app in self.apps:
            for fieldName, _type, fct in self.appInfo[app].rules:
                self.appInfo[app].profile[fieldName] = fct(self.appInfo[app].rootClass)
            
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
    print(eprofile.appInfo[app].profile)
