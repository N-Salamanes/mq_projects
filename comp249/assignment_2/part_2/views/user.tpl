<!DOCTYPE html>
<html lang="en">
  <head>

    <title>{{title}}</title>
      <link href="/static/style.css" rel="stylesheet">
  </head>

    <body>
        %if userlogged != None:
            <fieldset>
            <p>Logged in as {{userlogged}}</p>
            <form method="post" action="/logout" id="logoutform">
            <input type="submit" value="logout"/>
            </form>
            </fieldset>
        %end
    
    <h1>{{title}}</h1>

    <div class="content">

        <img src={{avatar}}>
        <br>
        <b>{{username}}</b>

        % for item in post:
            <p>{{!item}}</p>
        % end

    </div>


  </body>
</html>
