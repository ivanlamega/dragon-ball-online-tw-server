CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 819;
	title = 81902;

	CNtlTSGroup
	{
		gid = 0;

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
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 81907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 36;
				minlvl = 28;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 81909;
				ctype = 1;
				idx = 3031102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 81908;
				m1fx = "5008.000000";
				area = 81901;
				goal = 81904;
				m0fz = "842.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 81916;
				sort = 81905;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "869.000000";
				grade = 132203;
				m0fx = "4913.000000";
				m0ttip = 81915;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 81902;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 13;
				eitype = 0;
				idx0 = 7811101;
				cnt0 = 13;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 7812101;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 81914;
			nextlnk = 101;
			rwdtbl = 81901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5062101;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 81908;
			gtype = 2;
			oklnk = 2;
			area = 81901;
			goal = 81904;
			sort = 81905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 81902;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
}

