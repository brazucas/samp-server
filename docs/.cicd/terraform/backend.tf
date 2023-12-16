terraform {
    backend "s3" {
        bucket = "brztech-brz-gg-state"
        key    = "terraform/samp_docs.tfstate"
        region = "sa-east-1"
    }
}