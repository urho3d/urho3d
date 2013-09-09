![Civetweb](https://raw.github.com/sunsetbrew/civetweb/master/resources/civetweb_64x64.png "Civetweb") Civetweb
=======

Project Mission
-----------------

Project mission is to provide easy to use, powerful, C/C++ embeddable web server with optional CGI, SSL and Lua support.
Civetweb has a MIT license so you can innovate without restrictions.

Where to find the official version?
-----------------------------------

End users can download Civetweb at SourceForge
https://sourceforge.net/projects/civetweb/

Developers can contribute to CivetWeb via GitHub
https://github.com/sunsetbrew/civetweb

Trouble tickets should be filed on GitHub
https://github.com/sunsetbrew/civetweb/issues

Discussion group is at Google Groups
https://groups.google.com/d/forum/civetweb

Quick start documentation
--------------------------

- [docs/Installing.md](https://github.com/sunsetbrew/civetweb/blob/master/docs/Installing.md) - Install Guide
- [docs/UserManual.md](https://github.com/sunsetbrew/civetweb/blob/master/docs/UserManual.md) - End User Guide
- [docs/Building.md](https://github.com/sunsetbrew/civetweb/blob/master/docs/Building.md) - Buildiing the Server Quick Start
- [docs/Embedding.md](https://github.com/sunsetbrew/civetweb/blob/master/docs/Embedding.md) - Embedding Quick Start
- [RELEASE_NOTES.md](https://github.com/sunsetbrew/civetweb/blob/master/RELEASE_NOTES.md) - Release Notes
- [LICENSE.md](https://github.com/sunsetbrew/civetweb/blob/master/LICENSE.md) - Copyright License

Overview
--------

Civetweb keeps the balance between functionality and
simplicity by carefully selected list of features:

- Liberal, commercial-friendly, permissive,
  [MIT license](http://en.wikipedia.org/wiki/MIT_License)
- Free from copy-left licenses, like GPL, because you should innovate without restrictions.
- Based on [Mongoose](https://code.google.com/p/mongoose/)
- Works on Windows, Mac, UNIX, iPhone, Android, Buildroot, and many other platforms
- Scripting and database support (Lua Server Pages + Sqlite
  which provides ready to go, powerful web development platform in
  one single-click executable with **no dependencies**: forget LAMP!
- Support for CGI, SSL, SSI, Digest (MD5) authorization, Websocket, WEbDAV
- Resumed download, URL rewrite, file blacklist, IP-based ACL, Windows service
- Download speed limit based on client subnet or URI pattern
- Simple and clean embedding API,
  The source is in single file
  to make things easy. Embedding examples included.
- HTTP client capable of sending arbitrary HTTP/HTTPS requests


### Other optionally included software

<a href="http://lua.org">
![Lua](https://raw.github.com/sunsetbrew/civetweb/master/resources/lua-logo.jpg "Lua Logo")
</a>
<a href="http://sqlite.org">
![Sqlite3](https://raw.github.com/sunsetbrew/civetweb/master/resources/sqlite3-logo.jpg "Sqlite3 Logo")
</a>

Support
-------

The original Mongoose project is recommended if support is needed.  However,
this is very easy to install and use. 

Contributions
---------------

Contributions are welcome provided all contributions carry the MIT license.

DO NOT APPLY fixes copied from Mongoose to this project to prevent GPL tainting.

### Author

The original Author was Sergey Lyubka.  He still controls the original
Mongoose project.  However, he has changed or said he would 
change licenses after writing and distributing the original code this
project is based on.

Using this project ensures the MIT licenses terms are applied and
GPL cannot be imposed on any of this code as long as it is sourced from
here.

For the latest and greatest code and features, please use the Mongoose
code from Sergey Lyubka.  However, doing so will require adherence to
the new licenses.

This project ensures that GPL license cannot be applied to this code.
This code will remain free with the MIT license protection.
