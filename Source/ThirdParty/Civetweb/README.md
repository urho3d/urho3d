![Civetweb](https://raw.github.com/bel2125/civetweb/master/resources/civetweb_64x64.png "Civetweb") Civetweb
=======

There is a new home!!!
-----------------
https://github.com/bel2125/civetweb

Bel has been taking the lead on Civetweb, so the official repository is being
moved under his control for ease of maintenance.

Project Mission
-----------------

Project mission is to provide easy to use, powerful, C/C++ embeddable web
server with optional CGI, SSL and Lua support.
Civetweb has a MIT license so you can innovate without restrictions.

Where to find the official version?
-----------------------------------

End users can download Civetweb at SourceForge
https://sourceforge.net/projects/civetweb/

Developers can contribute to CivetWeb via GitHub
https://github.com/bel2125/civetweb

Trouble tickets should be filed on GitHub
https://github.com/bel2125/civetweb/issues

Discussion/support group and announcements are at Google Groups
https://groups.google.com/d/forum/civetweb

Quick start documentation
--------------------------

- [docs/Installing.md](https://github.com/bel2125/civetweb/blob/master/docs/Installing.md) - Install Guide
- [docs/UserManual.md](https://github.com/bel2125/civetweb/blob/master/docs/UserManual.md) - End User Guide
- [docs/Building.md](https://github.com/bel2125/civetweb/blob/master/docs/Building.md) - Buildiing the Server Quick Start
- [docs/Embedding.md](https://github.com/bel2125/civetweb/blob/master/docs/Embedding.md) - Embedding Quick Start
- [RELEASE_NOTES.md](https://github.com/bel2125/civetweb/blob/master/RELEASE_NOTES.md) - Release Notes
- [LICENSE.md](https://github.com/bel2125/civetweb/blob/master/LICENSE.md) - Copyright License

Overview
--------

Civetweb keeps the balance between functionality and
simplicity by a carefully selected list of features:

- Liberal, commercial-friendly, permissive,
  [MIT license](http://en.wikipedia.org/wiki/MIT_License)
- Free from copy-left licenses, like GPL, because you should innovate without
  restrictions.
- Forked from [Mongoose](https://code.google.com/p/mongoose/) in 2013, before
  it changed the licence from MIT to commercial + GPL. A lot of enchancements
  have been added since that time, see
  [RELEASE_NOTES.md](https://github.com/bel2125/civetweb/blob/master/RELEASE_NOTES.md).
- Works on Windows, Mac, Linux, UNIX, iPhone, Android, Buildroot, and many
  other platforms.
- Scripting and database support (Lua scipts, Lua Server Pages, CGI + SQLite
  database).
  This provides a ready to go, powerful web development platform in a one
  single-click executable with **no dependencies**.
- Support for CGI, HTTPS/SSL, SSI, HTTP digest (MD5) authorization, Websocket,
  WEbDAV.
- Resumed download, URL rewrite, file blacklist, IP-based ACL, Windows service.
- Download speed limit based on client subnet or URI pattern.
- Simple and clean embedding API.
- The source is in single file to make things easy.
- Embedding examples included.
- HTTP client capable of sending arbitrary HTTP/HTTPS requests.


### Optionally included software

<a href="http://lua.org">
![Lua](https://raw.github.com/bel2125/civetweb/master/resources/lua-logo.jpg "Lua Logo")
</a>
<a href="http://sqlite.org">
![Sqlite3](https://raw.github.com/bel2125/civetweb/master/resources/sqlite3-logo.jpg "Sqlite3 Logo")
</a>
<a href=http://keplerproject.github.io/luafilesystem/">
![LuaFileSystem](https://raw.github.com/bel2125/civetweb/master/resources/luafilesystem-logo.jpg "LuaFileSystem Logo")
</a>
<a href=http://lua.sqlite.org/index.cgi/index">
![LuaSQLite3](https://raw.github.com/bel2125/civetweb/master/resources/luasqlite-logo.jpg "LuaSQLite3 Logo")
</a>
<a href=http://viremo.eludi.net/LuaXML/index.html">
![LuaXML](https://raw.github.com/bel2125/civetweb/master/resources/luaxml-logo.jpg "LuaXML Logo")
</a>

Support
-------

This project is very easy to install and use. Please read the [documentation](https://github.com/bel2125/civetweb/blob/master/docs/)
and have a look at the [examples] (https://github.com/bel2125/civetweb/blob/master/examples/).
More information may be found on the [mailing list](https://groups.google.com/d/forum/civetweb).


Contributions
---------------

Contributions are welcome provided all contributions carry the MIT license.

DO NOT APPLY fixes copied from Mongoose to this project to prevent GPL tainting.

### Author

Civetweb is based on the Mongoose project - the original Author was Sergey Lyubka.  He still
controls the original Mongoose project.  However, he has changed or said he would
change licenses after writing and distributing the original code this
project is based on.

Using this project ensures the MIT licenses terms are applied and
GPL cannot be imposed on any of this code as long as it is sourced from
here. This code will remain free with the MIT license protection.

A list of authors can be found in [CREDITS.md](https://github.com/bel2125/civetweb/blob/master/CREDITS.md)

