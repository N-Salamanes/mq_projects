<!DOCTYPE html>
<html lang="en">
  <head>

    <title>{{title}}</title>
      <link href="/static/style.css" rel="stylesheet">
  </head>

  <body>
    <fieldset>
        <form method="post" action="/login" id="loginform">
            <legend>Enter login details</legend>
            <ul>
                <li>Username: <input name='nick'></li>
                <li>Password: <input name='password'></li>
            </ul>
            <input type='submit' value='Login'/>
                <p>Login Failed, please try again</p>
        </form>
    </fieldset>
    </form>


    <h1>{{title}}</h1>


    <div class="content">

    </div>


  </body>
</html>
