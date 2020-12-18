__author__ = 'Steve Cassidy'

from bottle import Bottle, template, static_file, request, response, HTTPError
import interface
import users
from database import COMP249Db


application = Bottle()

@application.route('/')
def index():

    db = COMP249Db()

    list_posts = interface.post_list(db)

    return template('general', title="Psst!", content="Welcome to Psst!", post=list_posts)

@application.route('/users/<user>')
def user(user):

    db = COMP249Db()

    list_posts = interface.post_list(db, user)

    #since we know exactly what position the avatar is, we can hard code it and pass it
    avatar = list_posts[0][3]

    return template('user', title="Page for " + user, content=user, post=list_posts, avatar=avatar)

@application.route('/mentions/<user>')
def mention(user):

    db = COMP249Db()

    list_mentions = interface.post_list_mentions(db, user)

    return template('mentions', title="Mentions for " + user, content=user, post=list_mentions)


@application.route('/static/<filename:path>')
def static(filename):
    return static_file(filename=filename, root='static')




if __name__ == '__main__':
    application.run(debug=True)