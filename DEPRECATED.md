# DEPRECATED

As of release 1.3.0, Envoy will follow a
[Breaking Change Policy](https://github.com/lyft/envoy/blob/master//CONTRIBUTING.md#breaking-change-policy).

The following features have been DEPRECATED and will be removed in the specified release cycle.

## Version 1.4.0

* Config option `statsd_local_udp_port` has been deprecated and has been replaced with
  `statsd_udp_ip_address`.
* `HttpFilterConfigFactory` filter API has been deprecated in favor of `NamedHttpFilterConfigFactory`.
* Config option `http_codec_options` has been deprecated and has been replaced with `http2_settings`.
* The following log macros have been deprecated: `log_trace`, `log_debug`, `conn_log`,
  `conn_log_info`, `conn_log_debug`, `conn_log_trace`, `stream_log`, `stream_log_info`,
  `stream_log_debug`, `stream_log_trace`.  For replacements, please see
  [logger.h](https://github.com/lyft/envoy/blob/master/source/common/common/logger.h).
* The connectionId() and ssl() callbacks of StreamFilterCallbacks have been deprecated and
  replaced with a more general connection() callback, which, when not returning a nullptr, can be
  used to get the connection id and SSL connection from the returned Connection object pointer.
* The protobuf stub gRPC support via `Grpc::RpcChannelImpl` is now replaced with `Grpc::AsyncClientImpl`.
  This no longer uses `protoc` generated stubs but instead utilizes C++ template generation of the
  RPC stubs. `Grpc::AsyncClientImpl` supports streaming, in addition to the previous unary, RPCs.
* The direction of network and HTTP filters in the configuration will be ignored from 1.4.0 and
  later removed from the configuration in the v2 APIs. Filter direction is now implied at the C++ type
  level.
