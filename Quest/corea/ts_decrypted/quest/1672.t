CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1672;
	title = 167202;

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
				conv = 167209;
				ctype = 1;
				idx = 3242106;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 167208;
				gtype = 0;
				area = 167201;
				goal = 167204;
				grade = 132203;
				rwd = 100;
				sort = 167205;
				stype = 1;
				taid = 1;
				title = 167202;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 167207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1667;";
			}
			CDboTSClickNPC
			{
				npcidx = 3242106;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 167208;
			gtype = 0;
			oklnk = 2;
			area = 167201;
			goal = 167204;
			sort = 167205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 167202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 167214;
			nextlnk = 254;
			rwdtbl = 167201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5533403;
			}
		}
	}
}

