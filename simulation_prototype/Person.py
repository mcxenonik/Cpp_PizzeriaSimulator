from PersonInterface import PersonInterface


class Person(PersonInterface):
    def __init__(self, new_id, new_name="Stefan"):
        super().__init__()

        self._ID = new_id
        self._name = new_name


    def getID(self):
        return self._ID


    def getName(self):
        return self._name