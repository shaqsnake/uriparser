<!--
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-06-28 11:18:03
 * @Description: A readme file of uriparser written by markdown.
 -->
# uriparser

uriparser是一个用C++实现的，符合[RFC3986](https://tools.ietf.org/html/rfc3986)标准的URI解析器。

## URI简介

### 语法

通用URI语法包括一系列分层的由 scheme, authority, path, query, 和 fragment 参考的部件，如下所示：
```
URI         = scheme ":" hier-part [ "?" query ] [ "#" fragment ]

hier-part   = "//" authority path-abempty
            / path-absolute
            / path-rootless
            / path-empty
```

示例：
```
  foo://example.com:8042/over/there?name=ferret#nose
  \_/   \______________/\_________/ \_________/ \__/
   |           |            |            |        |
scheme     authority       path        query   fragment
   |   _____________________|__
  / \ /                        \
  urn:example:animal:ferret:nose
```

### URI组件及其正则表达式

#### Scheme

每个URI以一个Schema(格式)名称开始，它代表一个协议。

```
scheme      = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
```

```
# Regular Expression rule syntax:  scheme
[A-Za-z][A-Za-z0-9+\-.]*
```

#### Authority

用来描述一个命名的机构，通常是基于已注册的服务器地址, 还可以包含可选的端口和用户信息。
```
authority   = [ userinfo "@" ] host [ ":" port ]
```
- User Information: 用户信息包含一个用户名(可选)，用"@"符号和主机名分开。
- Host: 主机名可以由一个封装在方括号内的IP文字, 一个点分十进制格式的IPv4地址, 或一个注册名称来标识。
- Port: 端口号(可选)跟随在主机名后面，用单个的冒号 (":") 字符之后开始的十进制数字。

```
# Regular Expression rule syntax:  authority
(?: (?:[A-Za-z0-9\-._~!$&'()*+,;=:]|%[0-9A-Fa-f]{2})* @)?     # [ userinfo "@" ]
(?:                                                           # host
  \[
  (?:
    (?:
      (?:                                                    (?:[0-9A-Fa-f]{1,4}:){6}
      |                                                   :: (?:[0-9A-Fa-f]{1,4}:){5}
      | (?:                            [0-9A-Fa-f]{1,4})? :: (?:[0-9A-Fa-f]{1,4}:){4}
      | (?: (?:[0-9A-Fa-f]{1,4}:){0,1} [0-9A-Fa-f]{1,4})? :: (?:[0-9A-Fa-f]{1,4}:){3}
      | (?: (?:[0-9A-Fa-f]{1,4}:){0,2} [0-9A-Fa-f]{1,4})? :: (?:[0-9A-Fa-f]{1,4}:){2}
      | (?: (?:[0-9A-Fa-f]{1,4}:){0,3} [0-9A-Fa-f]{1,4})? ::    [0-9A-Fa-f]{1,4}:
      | (?: (?:[0-9A-Fa-f]{1,4}:){0,4} [0-9A-Fa-f]{1,4})? ::
      ) (?:
          [0-9A-Fa-f]{1,4} : [0-9A-Fa-f]{1,4}
        | (?: (?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?) \.){3}
              (?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)
        )
    |   (?: (?:[0-9A-Fa-f]{1,4}:){0,5} [0-9A-Fa-f]{1,4})? ::    [0-9A-Fa-f]{1,4}
    |   (?: (?:[0-9A-Fa-f]{1,4}:){0,6} [0-9A-Fa-f]{1,4})? ::
    )
  | [Vv][0-9A-Fa-f]+\.[A-Za-z0-9\-._~!$&'()*+,;=:]+
  )
  \]
| (?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}
     (?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)
| (?:[A-Za-z0-9\-._~!$&'()*+,;=]|%[0-9A-Fa-f]{2})*
)
(?: : [0-9]* )?                                               # [ ":" port ]
```

#### Path

路径包含数据, 常常组织成层次格式, 它连同非层次化的查询(Query), 用于识别在该URI的格式和命名机构(如果有)范围内的一个资源；路径由第一个问号("?")或数字符号("#")字符或该URI的结尾来终止。
```
path          = path-abempty    ; begins with "/" or is empty
              / path-absolute   ; begins with "/" but not "//"
              / path-noscheme   ; begins with a non-colon segment
              / path-rootless   ; begins with a segment
              / path-empty      ; zero characters

path-abempty  = *( "/" segment )
path-absolute = "/" [ segment-nz *( "/" segment ) ]
path-noscheme = segment-nz-nc *( "/" segment )
path-rootless = segment-nz *( "/" segment )
path-empty    = 0<pchar>

segment       = *pchar
segment-nz    = 1*pchar
segment-nz-nc = 1*( unreserved / pct-encoded / sub-delims / "@" )
              ; non-zero-length segment without any colon ":"

pchar         = unreserved / pct-encoded / sub-delims / ":" / "@"
```
```
# Regular Expression rule syntax: path
(?:                                                             # (
    (?:/ (?:[A-Za-z0-9\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})* )*  #   path-abempty
| /                                                             # / path-absolute
  (?:    (?:[A-Za-z0-9\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})+
    (?:/ (?:[A-Za-z0-9\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})* )*
  )?
|        (?:[A-Za-z0-9\-._~!$&'()*+,;=@] |%[0-9A-Fa-f]{2})+     # / path-noscheme
    (?:/ (?:[A-Za-z0-9\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})* )*
|        (?:[A-Za-z0-9\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})+     # / path-rootless
    (?:/ (?:[A-Za-z0-9\-._~!$&'()*+,;=:@]|%[0-9A-Fa-f]{2})* )*
|                                                               # / path-empty
)                                                               # )
```

#### Query

查询包含非层次化的数据, 以及路径(Path), 用来从该URI的格式和命名机构(如果有)中识别一个资源；查询由第一个问号("?")字符指示并由一个数字符号("#")字符或该URI的结尾终止。
```
query       = *( pchar / "/" / "?" )
```
```
# Regular Expression rule syntax: query
(?:[A-Za-z0-9\-._~!$&'()*+,;=:@/?]|%[0-9A-Fa-f]{2})*
```

#### Fragment

一个URI的片段标识符部件允许对一个主要资源引用的次要资源的非直接身份认证以及额外的识别信息；片段标识符部件是通过一个数字符号("#")字符的出现来指示的并由该URI的结尾来终止。
```
fragment    = *( pchar / "/" / "?" )
```
```
# Regular Expression rule syntax: fragment
(?:[A-Za-z0-9\-._~!$&'()*+,;=:@/?]|%[0-9A-Fa-f]{2})*
```

## 参考资料
1. [RFC3986](https://tools.ietf.org/html/rfc3986)
2. [RFC3986 中文翻译](http://wiki.jabbercn.org/RFC3986#.E6.A0.BC.E5.BC.8F)
3. [StackOverflow 关于URI正则的问答](https://stackoverflow.com/questions/30847/regex-to-validate-uris)
4. [Regular Expression URI Validation](http://jmrware.com/articles/2009/uri_regexp/URI_regex.html)
