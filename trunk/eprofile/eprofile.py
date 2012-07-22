import logging
logging.basicConfig(level=logging.INFO)

class Application:
    trailManager = None
    profileManager = None
    name = 'None'

    def sendContext(self, context):
        self.profileManager.updateContextInfo(self, context)
        

#################################################################

class StudentApp(Application):
    name = 'StudentApp'

    def sendContext(self):
        f = open('things.owl')
        context = f.read()
        f.close()
        Application.sendContext(self, context)

    def registerRandomEvent(self):
        pass
        
#################################################################
        
class TrailManager:
    pass

#################################################################

class Eprofile:

    apps = set()
    contextInfo = {}

    def registerApp(self, app):
        logging.info('Application ' + app.name + ' registered.')
        self.apps.add(app)
        self.contextInfo[app] = None

    def updateContextInfo(self, app, context):
        logging.info('Context information for app ' + app.name + ' updated.')
        self.contextInfo[app] = context

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

    # application sends context information
    app.sendContext()

    # application register trails
    for _ in range(50):
        app.registerRandomEvent()

    
    
