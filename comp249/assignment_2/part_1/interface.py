"""
@author:
"""

import sqlite3
import time
import cgi
import html
import re

def post_to_html(content):
    """Convert a post to safe HTML, quote any HTML code, convert
    URLs to live links and spot any @mentions or #tags and turn
    them into links.  Return the HTML string"""

    #convert <, >, & to safe html excluding quotes
    s = html.escape(content, False)

    urls = re.compile(r"((https?):((//)|(\\\\))+[\w\d:#@%/;$()~_?\+-=\\\.&]*)", re.MULTILINE|re.UNICODE)

    #add anchor to link
    s = urls.sub(r"<a href='\1'>\1</a>", s)

    #add anchor to @users
    s = re.sub(r'(@)(\w*\.?\w+)',r"<a href='/users/\2'>\1\2</a>", s)

    return s

def post_list(db, usernick=None, limit=50):
    """Return a list of posts ordered by date
    db is a database connection (as returned by COMP249Db())
    if usernick is not None, return only posts by this user
    return at most limit posts (default 50)

    Returns a list of tuples (id, timestamp, usernick, avatar,  content)
    """

    #create cursor to the database
    cursor = db.cursor()

    #If usernick is specified or not, find posts accordingly
    if usernick == None:
        sqlQuery = """SELECT p.id, p.timestamp, p.usernick, u.avatar, p.content
        FROM posts p, users u
        WHERE p.usernick=u.nick
        ORDER BY timestamp DESC"""

        cursor.execute(sqlQuery)
    else:
        sqlQuery = """SELECT p.id, p.timestamp, p.usernick, u.avatar, p.content
        FROM posts p, users u
        WHERE p.usernick = (?) AND p.usernick=u.nick
        ORDER BY timestamp DESC"""

        cursor.execute(sqlQuery, (usernick,))


    return cursor.fetchall()[:limit]


def post_list_mentions(db, usernick, limit=50):
    """Return a list of posts that mention usernick, ordered by date
    db is a database connection (as returned by COMP249Db())
    return at most limit posts (default 50)

    Returns a list of tuples (id, timestamp, usernick, avatar,  content)
    """

    #create cursor to the database
    cursor = db.cursor()

    if usernick==None:
        qlQuery = """SELECT p.id, p.timestamp, p.usernick, u.avatar, p.content
        FROM posts p, users u
        WHERE p.usernick=u.nick AND p.content = '%@%'
        ORDER BY timestamp DESC"""

        cursor.execute(sqlQuery)
    else:
        sqlQuery = """SELECT p.id, p.timestamp, p.usernick, u.avatar, p.content
        FROM posts p, users u
        WHERE p.usernick=u.nick AND p.content LIKE ?
        ORDER BY timestamp DESC"""

        usernick = '%'+'@'+usernick+'%'

        cursor.execute(sqlQuery, (usernick,))


    return cursor.fetchall()[:limit]



def post_add(db, usernick, message):
    """Add a new post to the database.
    The date of the post will be the current time and date.

    Return a the id of the newly created post or None if there was a problem"""

    #check to see if the message length is below the threshold
    if len(message) <= 150:
        #create the cursor
        cursor = db.cursor()

        #sql query to execute
        sqlQuery = "INSERT INTO posts(usernick, content) VALUES(?, ?, ?)"

        #execute the query with arguments
        cursor.execute(sqlQuery, (usernick, message,))

        #comit the connection
        db.commit()

        #return the ID of the last inserted object
        return cursor.lastrowid
    else:
        return None



