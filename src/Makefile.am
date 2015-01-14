DIST_SUBDIRS = secp256k1
AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS)


if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(CXXFLAGS) $(CPPFLAGS)"
endif

Testcoin_CONFIG_INCLUDES=-I$(builddir)/config
Testcoin_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

Testcoin_INCLUDES += -I$(srcdir)/secp256k1/include

LIBTestcoin_SERVER=libTestcoin_server.a
LIBTestcoin_WALLET=libTestcoin_wallet.a
LIBTestcoin_COMMON=libTestcoin_common.a
LIBTestcoin_CLI=libTestcoin_cli.a
LIBTestcoin_UTIL=libTestcoin_util.a
LIBTestcoin_CRYPTO=crypto/libTestcoin_crypto.a
LIBTestcoin_UNIVALUE=univalue/libTestcoin_univalue.a
LIBTestcoinQT=qt/libTestcoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libTestcoin_crypto.a \
  libTestcoin_util.a \
  libTestcoin_common.a \
  univalue/libTestcoin_univalue.a \
  libTestcoin_server.a \
  libTestcoin_cli.a
if ENABLE_WALLET
Testcoin_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libTestcoin_wallet.a
endif

if BUILD_Testcoin_LIBS
lib_LTLIBRARIES = libTestcoinconsensus.la
LIBTestcoin_CONSENSUS=libTestcoinconsensus.la
else
LIBTestcoin_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =

if BUILD_TestcoinD
  bin_PROGRAMS += Testcoind
endif

if BUILD_Testcoin_UTILS
  bin_PROGRAMS += Testcoin-cli Testcoin-tx
endif

.PHONY: FORCE
# Testcoin core #
Testcoin_CORE_H = \
  addrman.h \
  alert.h \
  allocators.h \
  amount.h \
  arith_uint256.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparamsbase.h \
  chainparams.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compressor.h \
  core_io.h \
  crypter.h \
  db.h \
  eccryptoverify.h \
  ecwrapper.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  merkleblock.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  noui.h \
  pow.h \
  primitives/block.h \
  primitives/transaction.h \
  protocol.h \
  pubkey.h \
  random.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  script/interpreter.h \
  script/script_error.h \
  script/script.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  serialize.h \
  streams.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltime.h \
  version.h \
  walletdb.h \
  wallet.h \
  wallet_ismine.h \
  compat/sanity.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libTestcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between Testcoind and Testcoin-qt
libTestcoin_server_a_CPPFLAGS = $(Testcoin_INCLUDES) $(MINIUPNPC_CPPFLAGS)
libTestcoin_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  init.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  txdb.cpp \
  txmempool.cpp \
  $(JSON_H) \
  $(Testcoin_CORE_H)

# wallet: shared between Testcoind and Testcoin-qt, but only linked
# when wallet enabled
libTestcoin_wallet_a_CPPFLAGS = $(Testcoin_INCLUDES)
libTestcoin_wallet_a_SOURCES = \
  db.cpp \
  crypter.cpp \
  rpcdump.cpp \
  rpcwallet.cpp \
  wallet.cpp \
  wallet_ismine.cpp \
  walletdb.cpp \
  $(Testcoin_CORE_H)

# crypto primitives library
crypto_libTestcoin_crypto_a_CPPFLAGS = $(Testcoin_CONFIG_INCLUDES)
crypto_libTestcoin_crypto_a_SOURCES = \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  crypto/hmac_sha256.cpp \
  crypto/rfc6979_hmac_sha256.cpp \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/common.h \
  crypto/sha256.h \
  crypto/sha512.h \
  crypto/hmac_sha256.h \
  crypto/rfc6979_hmac_sha256.h \
  crypto/hmac_sha512.h \
  crypto/sha1.h \
  crypto/ripemd160.h

# univalue JSON library
univalue_libTestcoin_univalue_a_SOURCES = \
  univalue/univalue.cpp \
  univalue/univalue_read.cpp \
  univalue/univalue_write.cpp \
  univalue/univalue_escapes.h \
  univalue/univalue.h

# common: shared between Testcoind, and Testcoin-qt and non-server tools
libTestcoin_common_a_CPPFLAGS = $(Testcoin_INCLUDES)
libTestcoin_common_a_SOURCES = \
  allocators.cpp \
  arith_uint256.cpp \
  amount.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  core_read.cpp \
  core_write.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  protocol.cpp \
  pubkey.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/sign.cpp \
  script/standard.cpp \
  script/script_error.cpp \
  $(Testcoin_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libTestcoin_util_a_CPPFLAGS = $(Testcoin_INCLUDES)
libTestcoin_util_a_SOURCES = \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpcprotocol.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(Testcoin_CORE_H)

if GLIBC_BACK_COMPAT
libTestcoin_util_a_SOURCES += compat/glibc_compat.cpp
libTestcoin_util_a_SOURCES += compat/glibcxx_compat.cpp
endif

# cli: shared between Testcoin-cli and Testcoin-qt
libTestcoin_cli_a_CPPFLAGS = $(Testcoin_INCLUDES)
libTestcoin_cli_a_SOURCES = \
  rpcclient.cpp \
  $(Testcoin_CORE_H)

nodist_libTestcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# Testcoind binary #
Testcoind_LDADD = \
  $(LIBTestcoin_SERVER) \
  $(LIBTestcoin_COMMON) \
  $(LIBTestcoin_UNIVALUE) \
  $(LIBTestcoin_UTIL) \
  $(LIBTestcoin_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_WALLET
Testcoind_LDADD += libTestcoin_wallet.a
endif
Testcoind_SOURCES = Testcoind.cpp
#

if TARGET_WINDOWS
Testcoind_SOURCES += Testcoind-res.rc
endif

Testcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
Testcoind_CPPFLAGS = $(Testcoin_INCLUDES)
Testcoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

# Testcoin-cli binary #
Testcoin_cli_LDADD = \
  $(LIBTestcoin_CLI) \
  $(LIBTestcoin_UTIL) \
  $(BOOST_LIBS) \
  $(SSL_LIBS) \
  $(CRYPTO_LIBS)

Testcoin_cli_SOURCES = \
  Testcoin-cli.cpp

Testcoin_cli_CPPFLAGS = $(Testcoin_INCLUDES)
#

# Testcoin-tx binary #
Testcoin_tx_LDADD = \
  $(LIBTestcoin_UNIVALUE) \
  $(LIBTestcoin_COMMON) \
  $(LIBTestcoin_UTIL) \
  $(LIBTestcoin_CRYPTO) \
  $(LIBSECP256K1) \
  $(BOOST_LIBS) \
  $(CRYPTO_LIBS)

Testcoin_tx_SOURCES = Testcoin-tx.cpp
Testcoin_tx_CPPFLAGS = $(Testcoin_INCLUDES)
#
Testcoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
Testcoin_cli_SOURCES += Testcoin-cli-res.rc
endif
Testcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if BUILD_Testcoin_LIBS
include_HEADERS = script/Testcoinconsensus.h
libTestcoinconsensus_la_SOURCES = \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  script/Testcoinconsensus.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libTestcoinconsensus_la_SOURCES += compat/glibc_compat.cpp
  libTestcoinconsensus_la_SOURCES += compat/glibcxx_compat.cpp
endif

libTestcoinconsensus_la_LDFLAGS = -no-undefined $(RELDFLAGS)
libTestcoinconsensus_la_LIBADD = $(CRYPTO_LIBS)
libTestcoinconsensus_la_CPPFLAGS = $(CRYPTO_CFLAGS) -I$(builddir)/obj -DBUILD_Testcoin_INTERNAL
if USE_LIBSECP256K1
libTestcoinconsensus_la_LIBADD += secp256k1/libsecp256k1.la
endif
endif

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
