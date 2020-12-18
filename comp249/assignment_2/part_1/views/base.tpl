<!DOCTYPE html>
<html lang="en">
  <head>

    <title>{{title}}</title>
      <link href="/static/style.css" rel="stylesheet">
  </head>

  <body>

    <h1>{{title}}</h1>

    <div class="content">

        {{!base}}

        % for item in post:
            <p>{{item}}</p>
        % end

    </div>


  </body>
</html>
