CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1512;
	title = 151202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 6;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 151209;
				ctype = 1;
				idx = 2801301;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 151208;
				m1fx = "-2113.000000";
				m2fz = "2236.000000";
				m1fy = "0.000000";
				sort = 151205;
				m2widx = 1;
				grade = 132203;
				m0fx = "-2221.000000";
				m0ttip = 151215;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 151202;
				gtype = 3;
				area = 151201;
				goal = 151204;
				m0fz = "2288.000000";
				m0widx = 1;
				m1ttip = 151216;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "2116.000000";
				m2fx = "-2186.000000";
				m2ttip = 151217;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 2;
				eitype = 0;
				idx0 = 7211102;
				cnt0 = 1;
				cnt2 = 3;
				ectype = -1;
				etype = 0;
				idx1 = 7213102;
				taid = 3;
				esctype = 0;
				idx2 = 7212102;
			}
		}
		CDboTSContGAct
		{
			cid = 6;
			elnk = 255;
			nextlnk = 3;
			prelnk = "2;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 3000;
			}
		}
		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 100;
			prelnk = "4;";

			CDboTSActWorldPlayScript
			{
				sid = 1512;
				start = 0;
				taid = 1;
				uof = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 252;
			nextlnk = 4;
			prelnk = "6;";

			CDboTSActWorldPlayScript
			{
				sid = 1512;
				start = 1;
				taid = 1;
				uof = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 151214;
			nextlnk = 101;
			rwdtbl = 151201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "5;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2801301;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 151207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2801301;
			}
			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 151208;
			gtype = 3;
			oklnk = 2;
			area = 151201;
			goal = 151204;
			sort = 151205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 151202;
		}
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
			nolnk = 255;
			rm = 0;
			yeslnk = 5;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "3;2;";
		}
	}
}

