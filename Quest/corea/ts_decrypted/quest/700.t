CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 700;
	title = 70002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 70009;
				ctype = 1;
				idx = 3173101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 70008;
				gtype = 1;
				area = 70001;
				goal = 70004;
				grade = 132203;
				rwd = 100;
				sort = 70005;
				stype = 2;
				taid = 1;
				title = 70002;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 70007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3173101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 31;
				minlvl = 23;
			}
			CDboTSCheckClrQst
			{
				and = "699;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 70008;
			gtype = 1;
			oklnk = 2;
			area = 70001;
			goal = 70004;
			sort = 70005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 70002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 70014;
			nextlnk = 254;
			rwdtbl = 70001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3032104;
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
			prelnk = "100;";
			type = 1;
		}
	}
}

