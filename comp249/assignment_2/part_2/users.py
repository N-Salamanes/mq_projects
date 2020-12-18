"""
@author:
"""

import bottle
import uuid
import sqlite3

# this variable MUST be used as the name for the cookie used by this application
COOKIE_NAME = 'sessionid'

def check_login(db, usernick, password):
    """returns True if password matches stored"""

    #create cursor to the database
    cursor = db.cursor()

    #sql query to execute
    sqlQuery = "SELECT password FROM users WHERE nick = (?)"

    #execute the query with arguments, retrieve the stored crypted password
    cursor.execute(sqlQuery, (usernick,))

    #retrieve the stored encrypted password and compare it with the password being matched
    for row in cursor:
        if row[0] == db.crypt(password):
            #correct username and password, return True
            return True
    #no match
    return False


def generate_session(db, usernick):
    """create a new session and add a cookie to the request object (bottle.request)
    user must be a valid user in the database, if not, return None
    There should only be one session per user at any time, if there
    is already a session active, use the existing sessionid in the cookie
    """

    #create cursor to the database
    cursor = db.cursor()

    #sql query to execute
    sqlQuery = "SELECT sessionid FROM sessions WHERE usernick = (?)"

    #execute the query with arguments, grab the sessionid from the database if it exists
    cursor.execute(sqlQuery, (usernick,))

    #check to see if there is a current sessionid
    for row in cursor:
        if len(row[0])>0:
            #sessionid exists
            #set the cookie and return sessionid
            bottle.response.set_cookie(COOKIE_NAME, row[0])
            return row[0]

    #sql query to execute
    sqlQuery = "SELECT nick FROM users WHERE nick = (?)"

    #execute the query with arguments, see if the username is valid
    cursor.execute(sqlQuery, (usernick,))

    for row in cursor:
        #if the username is in the database
        if row[0] == usernick:
            #generate a sessionid
            sessionid = str(uuid.uuid4())

            #sql query to execute
            sqlQuery = "INSERT INTO sessions VALUES(?, ?)"

            #execute the query with arguments
            cursor.execute(sqlQuery, (sessionid, usernick))

            #commit the connection
            db.commit()

            #create our cookie
            bottle.response.set_cookie(COOKIE_NAME, sessionid)

            #return the session id
            return sessionid
        else:
            #Not a valid user
            return None





def delete_session(db, usernick):
    """remove all session table entries for this user"""

    #create cursor to the database
    cursor = db.cursor()

    #sql query to execute
    sqlQuery = "DELETE FROM sessions WHERE usernick = (?)"

    #execute the query with arguments
    cursor.execute(sqlQuery, (usernick,))

    #commit the connection
    db.commit()



def session_user(db):
    """try to
    retrieve the user from the sessions table
    return usernick or None if no valid session is present"""

    #grab the cookie stored
    cookie = bottle.request.get_cookie(COOKIE_NAME)

    #create cursor to execute
    cursor = db.cursor()

    #sql query to execute
    sqlQuery = "SELECT usernick FROM sessions WHERE sessionid = (?)"

    #execute the query with arguments
    cursor.execute(sqlQuery, (str(cookie),))

    for row in cursor:

        if len(row[0])>0:
            return row[0]
        else:
            return None

def add_user(db, usernick, password):

    cursor = db.cursor()

    avatar = "http://robohash.org/" + usernick
    try:
        sql = "INSERT INTO users (nick, password, avatar) VALUES (?, ?, ?)"
        cursor.execute(sql, (usernick, db.crypt(password), avatar,))
        sql = "INSERT INTO follows (followed, follower) VALUES (?, ?)"
        cursor.execute(sql, [usernick, usernick])

        db.commit()

        return True
    except sqlite3.IntegrityError:
        return False
