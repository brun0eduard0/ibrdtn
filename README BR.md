IBR-DTN - A modular and lightweight implementation of the bundle protocol.
==========================================================================

[Github - brun0eduard0](https://github.com/brun0eduard0/ibrdtn)

# Linux - Debian #

Você pode usar 1 único arquivo para realizar a instalação ou realizar os vários passos a seguir:
### Modo Fácil ###
 Ir na pasta "scripts" e executar 

    chmod +x linux-compile-complete.sh

    ./linux-compile-complete.sh

### Modo trabalhoso ###

A seguir: Requisitos, Instalação e configuração de variável de ambiente

## Requisitos ##

Conforme consta na descrição de instalação da ferramenta:

sudo apt-get install build-essential libssl-dev libz-dev libsqlite3-dev \
    libcurl4-gnutls-dev libdaemon-dev automake autoconf pkg-confg libtool libcppunit-dev \
    libnl-3-dev libnl-cli-3-dev libnl-genl-3-dev libnl-nf-3-dev libnl-route-3-dev libarchive-dev \
    libarchive-dev

## Instalação ##

Para fazer a instalação em computadores Linux, siga os seguintes passos:

git clone https://github.com/brun0eduard0/ibrdtn.git

cd ibrdtn/scripts/

    chmod +x linux-compile.sh

    ./linux-compile.sh

### Configurar Variável de Ambiente ###

echo "export LD_LIBRARY_PATH=/usr/local:/usr/local" >> ~/.bashrc

export LD_LIBRARY_PATH=/usr/local/:/usr/local

## About ##

This implementation of the bundle protocol RFC5050 is designed for embedded
systems like the RouterBoard 532A or Ubiquiti RouterStation Pro and can be
used as framework for DTN applications.

The module-based architecture with miscellaneous interfaces, makes it possible
to change functionalities like routing or storage of bundle just by inheriting
a specific class.

## Links ##

 * [Installation Instructions and Documentation](https://github.com/ibrdtn/ibrdtn/wiki)

## Features ##

 * Bundle Protocol (RFC 5050)
 * Bundle Security Protocol (RFC 6257)
 * Socket based API
 * AgeBlock support and bundle age tracking (draft-irtf-dtnrg-bundle-age-block-01)
 * Scope Control Hop Limit Block support
 * Experimental support for compressed bundle payload
 * Bundle-in-Bundle support
 * IPv6 support
 * Applications: dtnsend, dtnrecv, dtntrigger, dtnping, dtntracepath, dtninbox, dtnoutbox, dtnstream

## Convergence Layer ##
 
  * TCP/IP convergence layer (RFC 7242)
  * TLS extension for TCP convergence layer by Stephen Röttger
  * UDP/IP convergence layer - draft-irtf-dtnrg-udp-clayer-00
  * IP neighbor discovery based on draft-irtf-dtnrg-ipnd-01
  * HTTP convergence layer by Robert Heitz (Java Servlet)
  * IEEE 802.15.4 LoWPAN convergence layer by Stefan Schmidt

## Routing Modules ##
 
  * Routing with static connections
  * Forward bundles on discovery
  * Epidemic routing with bloomfilter
  * Flooding routing scheme
  * PRoPHET Routing

## Storage Modules ##

  * Memory-based storage
  * Persistent storage in file-system
  * SQLite Storage
