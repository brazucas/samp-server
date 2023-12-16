const { createServer, proxy } = require("aws-serverless-express");
const { eventContext } = require("aws-serverless-express/middleware");

const express = require("express");

const binaryMimeTypes = [
  "image/jpeg",
  "image/png",
  "image/webp",
  "image/gif",
  "image/svg+xml",
  "image/svg",
  "image/x-icon",
  "image/ico+xml",
];

let cachedServer;

function bootstrapServer() {
  const base = "/";

  if (!cachedServer) {
    const expressApp = express();
    expressApp.use(base, express.static("build/"));
    expressApp.use(eventContext());
    cachedServer = createServer(expressApp, undefined, binaryMimeTypes);
  }

  return cachedServer;
}

const handler = async (event, context) => {
  cachedServer = bootstrapServer();
  return proxy(cachedServer, event, context, "PROMISE").promise;
};

exports.handler = handler;
