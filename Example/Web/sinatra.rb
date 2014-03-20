require 'sinatra'
require 'json'
require 'protocol_buffers'

require_relative './person.pb.rb'
PHONE_COUNT = 1000

get '/1/getGroups' do
  content_type 'application/octet-stream'
  n = Person::PhoneNumber.new(:number => "number", :type => Person::PhoneType::MOBILE)
  p = Person.new(:personId => 123, :name => "name", :email => 'email@mail.aa')
  p.phones << n

  result = Array.new
  PHONE_COUNT.times do |x|
    n = Person::PhoneNumber.new(:number => "number" + x.to_s, :type => Person::PhoneType::MOBILE)
    p.phones << n
  end
  p.serialize_to_string
end

get '/1/getGroupsJson' do
  content_type 'application/json'

  list = Array.new
  list << {:number => "number", :type => 0}
  p = {:personId => 123, :name => "name", :email => 'email@mail.aa'}

  PHONE_COUNT.times do |x|
    list << {:number => "number" + x.to_s, :type => 0}
  end
  p[:phones] = list
  p.to_json
end