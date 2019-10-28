CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 773;
	title = 77302;

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
				conv = 77309;
				ctype = 1;
				idx = 1311101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 77308;
				gtype = 1;
				area = 77301;
				goal = 77304;
				grade = 132203;
				rwd = 100;
				sort = 77305;
				stype = 2;
				taid = 1;
				title = 77302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 77307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1311101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 34;
				minlvl = 26;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 77308;
			gtype = 1;
			oklnk = 2;
			area = 77301;
			goal = 77304;
			sort = 77305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 77302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 77314;
			nextlnk = 254;
			rwdtbl = 77301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3173201;
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
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

