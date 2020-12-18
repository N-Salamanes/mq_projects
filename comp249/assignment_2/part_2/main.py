__author__ = 'Steve Cassidy'

from bottle import Bottle, template, static_file, request, response, HTTPError, redirect
import interface
import users
from database import COMP249Db

COOKIE_NAME = 'sessionid'

application = Bottle()

db = COMP249Db()

@application.route('/')
def index():
    #try and get username if we are logged in
    userLogged = users.session_user(db)

    #grab the recent posts
    list_posts = interface.post_list(db)

    #tuple we are using to format the posts
    format_posts = []

    for post in list_posts:
        #format the avatar
        avatar = "<img src=" + post[3] + " height=50 width=50>"

        #format the userlink
        userlink = "<a href='/users/" + post[2] + "'>" + post[2] + "</a>"

        #combine the formatted values
        post = (avatar, userlink, post[1], interface.post_to_html(post[4]))

        #add the formatted post
        format_posts.append(post)

    #return the template
    return template('homepage', title="Psst!", post=format_posts, userlogged=userLogged)

@application.route('/register')
def register():
    #try and get username
    user = users.session_user(db)

    return template('register', title="Psst!", username=user)

@application.post('/reg')
def reg():
    #grab the username and password fields
    username = request.forms.get('nick')
    password = request.forms.get('password')

    #if add users successfully creates the user account
    if users.add_user(db, username, password):
        #successfully created
        response.status = 200

        return "Registered! <a href='/'>Click here to go back to homepage and login.</a>"
    else:
        #failed, user account already exists
        response.status = 200
        return """Username already registered, please select a unique username.<br>
        <a href='/register'>Click here to go back and try again</a>"""


@application.post('/post')
def post():
    #grab the content of the post
    myPost = request.forms.get('post')

    #gets the user from the current session
    user = users.session_user(db)

    #add the post to the database
    interface.post_add(db, user, myPost)

    #http response
    response.status = 303

    #go back to the root index
    response.set_header('Location', '/')

@application.post('/login')
def login_rdr():
    #grab the username and password fields
    username = request.forms.get('nick')
    password = request.forms.get('password')

    #check to see if login details match
    if users.check_login(db, username, password):
        #log in details match
        response.status = 303

        #generate session
        users.generate_session(db, username)

        #go back to the root index
        response.set_header('Location', '/')
    else:
        #log in details dont match
        response.status = 200

        #bring up retry template for another attempt
        return template('retry', title="Psst!")


@application.post('/logout')
def logout_rdr():
    #set our cookie to nothing
    response.set_cookie(COOKIE_NAME, "")

    #go back to the root index
    response.status = 303
    response.set_header('Location', '/')

@application.route('/users/<user>')
def user(user):
    #try and get username if we are logged in
    userLogged = users.session_user(db)

    #grab all the posts from the user
    list_posts = interface.post_list(db, user)

    #since we know exactly what position the avatar is, we can hard code it and pass it
    avatarBig = list_posts[0][3]

    #storing formatted posts here
    format_posts = []

    for post in list_posts:
        #format the avatar
        avatar = "<img src=" + post[3] + " height=50 width=50>"

        #format the userlink
        userlink = "<a href='/users/" + post[2] + "'>" + post[2] + "</a>"

        #combine the formatted values
        post = (avatar, userlink, post[1], interface.post_to_html(post[4]))

        #add the formatted post
        format_posts.append(post)

    #return the user template with arguments
    return template('user', title="Page for " + user, username=user, post=format_posts, avatar=avatarBig, userlogged=userLogged)

@application.route('/mentions/<user>')
def mention(user):
    #try and get username if we are logged in
    userLogged = users.session_user(db)

    #grab the list mentions according to user
    list_mentions = interface.post_list_mentions(db, user)

    #we use post_list here because sometimes the user might not have mentions and need to grab the correct avatar
    list_posts = interface.post_list(db, user)
    #since we know exactly what position the avatar is, we can hard code it and pass it
    avatarBig = list_posts[0][3]

    #formatted posts
    format_posts = []

    for post in list_mentions:
        #format the avatar
        avatar = "<img src=" + post[3] + " height=50 width=50>"

        #format the userlink
        userlink = "<a href='/users/" + post[2] + "'>" + post[2] + "</a>"

        #combine the formatted values
        post = (avatar, userlink, post[1], interface.post_to_html(post[4]))

        #add the formatted post
        format_posts.append(post)

    #return the mentions template with arguments
    return template('mentions', title="Mentions for " + user, username=user, post=format_posts, avatar=avatarBig, userlogged=userLogged)


@application.route('/static/<filename:path>')
def static(filename):
    return static_file(filename=filename, root='static')


if __name__ == '__main__':
    application.run(debug=True)