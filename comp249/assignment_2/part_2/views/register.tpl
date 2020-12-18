<!DOCTYPE html>
<html lang="en">
  <head>

    <title>{{title}}</title>
      <link href="/static/style.css" rel="stylesheet">
  </head>

  <body>
    <fieldset>
        %if username == None:
        <form method="post" action="/reg" id="registerform">
            <legend>Enter registration details</legend>
            <ul>
                <li>Username: <input name='nick'></li>
                <li>Password: <input name='password'></li>
            </ul>
            <input type='submit' value='Register'/>
        </form>
        % else:
            <p>Logged in as {{username}}, please log out if you want to create another account.</p>
            <form method="post" action="/logout" id="logoutform">
            <input type="submit" value="logout"/>
            </form>
        % end
    </fieldset>

    <h1>{{title}}</h1>

    <div class="content">

    </div>


  </body>
</html>
