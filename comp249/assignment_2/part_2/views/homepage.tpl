<!DOCTYPE html>
<html lang="en">
    <head>
        <title>{{title}}</title>
        <link href="/static/style.css" rel="stylesheet">
    </head>

    <body>
        <fieldset>
        %if userlogged == None:
        <form method="post" action="/login" id="loginform">
            <legend>Enter login details</legend>
            <ul>
                <li>Username: <input name='nick'></li>
                <li>Password: <input name='password'></li>
            </ul>
            <input type='submit' value='Login'/>
            <br>
            <br>
            <a href="/register">Click here to register</a>
        </form>
        % else:
            <p>Logged in as {{userlogged}}</p>
            <form method="post" action="/logout" id="logoutform">
            <input type="submit" value="logout"/>
            </form>
        % end
        </fieldset>

        <h1>{{title}}</h1>
        <h2>Welcome to Psst!</h2>

        <div class="content">

        %if userlogged != None:
            <form method="post" action="/post" id="postform">
            <legend>Submit a post</legend>
            <ul><li>Write post: <input name='post'></li></ul>
            <input type='submit' value='Post!'/>
            <br>
            <br>
        %end

        % for item in post:
            <p>{{!item}}</p>
        % end

        </div>

    </body>
</html>
