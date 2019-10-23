CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1172;
	title = 117202;

	CNtlTSGroup
	{
		gid = 0;

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
			stdiag = 117207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5533301;
			}
			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 117214;
			nextlnk = 101;
			rwdtbl = 117201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5533301;
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
				conv = 117209;
				ctype = 1;
				idx = 5533301;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 117208;
				m1fx = "232.000000";
				area = 117201;
				goal = 117204;
				m0fz = "-426.000000";
				m0widx = 9;
				m1fy = "0.000000";
				m1ttip = 117216;
				sort = 117205;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-411.000000";
				grade = 132203;
				m0fx = "248.000000";
				m0ttip = 117215;
				m1widx = 9;
				rwd = 100;
				taid = 1;
				title = 117202;
				gtype = 4;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 12;
				eitype = 0;
				idx0 = 4813300;
				cnt0 = 12;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 6611500;
				taid = 3;
				esctype = 0;
				idx2 = -1;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 117208;
			gtype = 4;
			oklnk = 2;
			area = 117201;
			goal = 117204;
			sort = 117205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 117202;
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

