import module namespace json = "http://zorba.io/modules/json-xml";

let $json :=
  <li>list item</li>
let $options := { "json-format" : "JsonML-array" }
return json:serialize( $json, $options )

(: vim:set et sw=2 ts=2: :)
