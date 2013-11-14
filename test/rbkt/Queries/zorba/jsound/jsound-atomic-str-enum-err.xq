import module namespace jsv = "http://jsound.io/modules/validate"; 

let $jsd :=
{
  "$namespace" : "http://www.example.com/my-schema",
  "$types" : [
    {
      "$kind" : "atomic",
      "$name" : "a-string-enum",
      "$baseType" : "string",
      "$enumeration" : [ "foo", "bar"]
    }
  ]
}


let $instance := "baz-not-valid"

return
  jsv:jsd-validate ($jsd, "a-string-enum", $instance )
