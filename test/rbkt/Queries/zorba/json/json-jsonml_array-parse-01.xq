import module namespace json = "http://zorba.io/modules/json-xml";

let $json := '[ "li", "list item" ]'
let $options := { "json-format" : "JsonML-array" }
return json:parse( $json, $options )

(: vim:set et sw=2 ts=2: :)
