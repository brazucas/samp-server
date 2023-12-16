import { createServer, proxy } from "aws-serverless-express";
import { eventContext } from "aws-serverless-express/middleware.js";

import express from "express";

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

async function bootstrapServer() {
  const base = "/";

  if (!cachedServer) {
    const expressApp = express();
    expressApp.use(base, express.static("build/"));
    expressApp.use(eventContext());
    cachedServer = createServer(expressApp, undefined, binaryMimeTypes);
  }

  return cachedServer;
}

export const handler = async (event, context) => {
  cachedServer = await bootstrapServer();
  return proxy(cachedServer, event, context, "PROMISE").promise;
};
